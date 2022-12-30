#include "MainMenuState.h"

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }

    t.loadFromFile("External/images/mainmenu.jpg");
    this->background.setTexture(t);
    this->background.setScale(4.f, 4.f);
}
void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 310, 400, 50, "new_game_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["CONTINUE_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 370, 400, 50, "continue_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["AUTHOR_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 430, 400, 50, "author_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["GAME_QUIT_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 490, 400, 50, "exit_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["TEST_GAME"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 550, 400, 50, "test_game_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");

}

void MainMenuState::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Overture.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}

MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->initButtons();
    this->initSounds();
}
MainMenuState ::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}
void MainMenuState::updateKeyBinds()
{
    this->checkForQuit();
}
void MainMenuState::endState()
{
    cout << "End MainMenu" << endl;
}
bool MainMenuState::checkSaved()
{
    ifstream ifs("Save/PreviousBoard.ini");
    int a;
    ifs >> a;
    if (a <= 0)
        return false;
    return true;
}
void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["GAME_STATE_BTN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new ChooseModeState(this->app, this->states));
    }

    if (this->buttons["CONTINUE_STATE_BTN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 0, true));
    }
    
    if (this->buttons["AUTHOR_BTN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new Author(this->app, this->states));
    }

    if (this->buttons["GAME_QUIT_BTN"]->isPressed())
    {
        this->app->close();
    }

    if (this->buttons["TEST_GAME"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 0, false));
    }

}

void MainMenuState::update()
{
    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    //system("cls") ;
    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;

}
void MainMenuState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void MainMenuState::render(RenderTarget* target)
{
    if (!target)
        target = this->app;

    target->draw(this->background);
    this->renderButtons(target);
}

