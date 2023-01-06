 #include "MainMenuState.h"

void MainMenuState::initBackground()
{
    this->texture.loadFromFile("External/images/mainmenu1.png");
    this->background.setTexture(texture);
}

void MainMenuState::initButtons()
{
    
    this->buttons["GAME_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 375, 400, 50, "new_game_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["CONTINUE_STATE_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 435, 400, 50, "continue_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["INSTRUCTIONS_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 495, 400, 50, "instructions_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["AUTHOR_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 555, 400, 50, "author_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["GAME_QUIT_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 615, 400, 50, "exit_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
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
    this->initBackground();
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

bool MainMenuState::checkSaved()
{
    ifstream ifs("Save/PreviousBoard.ini");
    int a;
    ifs >> a;
    if (a <= 0)
        return false;
    return true;
}

void MainMenuState::endState()
{

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

    if (this->buttons["INSTRUCTIONS_BTN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new Instruction(this->app, this->states));
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

}

void MainMenuState::update()
{
    this->updateMousePositions();
    this->updateButtons();
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

