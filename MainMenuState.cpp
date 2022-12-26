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
    this->buttons["GAME_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 200, 400, 50, "new_game_button");
    this->buttons["CONTINUE_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 260, 400, 50, "continue_button");
    this->buttons["HIGH_SCORE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 320, 400, 50, "high_score_button");
    this->buttons["AUTHOR_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 380, 400, 50, "author_button");
    this->buttons["GAME_QUIT_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 440, 400, 50, "exit_button");
    this->buttons["TEST_GAME"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 500, 400, 50, "test_game_button");

}
MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->initButtons();
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
        this->states->push(new ChooseModeState(this->app, this->states));
    }

    if (this->buttons["GAME_QUIT_BTN"]->isPressed())
    {
        this->app->close();
    }

    if (this->buttons["TEST_GAME"]->isPressed())
    {
        this->states->push(new GameState(this->app, this->states, 0, false));
    }

    if (this->buttons["CONTINUE_STATE_BTN"]->isPressed())
    {
        this->states->push(new GameState(this->app, this->states, 0 , true));
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

