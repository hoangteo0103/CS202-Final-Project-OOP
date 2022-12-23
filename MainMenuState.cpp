#include "MainMenuState.h"

void MainMenuState::initFonts()
{
    std::cout << "In MainMenuState::initFonts(), line: " << __LINE__ << '\n';
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }

    t.loadFromFile("External/images/mainmenu.jpg");
    this->background.setTexture(t);
    this->background.setScale(4.f, 4.f);
}
void MainMenuState::initButtons()
{
    std::cout << "In MainMenuState::initButtons(), line: " << __LINE__ << '\n';
    this->buttons["GAME_STATE_BTN"] = new Button(app->getSize().x/2 - 200.0, 200 , 400, 50,
        &this->font, "New Game", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["CONTINUE_STATE_BTN"] = new Button(app->getSize().x / 2 - 200.0, 260, 400, 50,
        &this->font, "Continue", Color(70, 70, 70, 200)
        , Color(100, 100, 100, 255), Color(20, 20, 20, 200));

    this->buttons["HIGH_SCORE_BTN"] = new Button(app->getSize().x / 2 - 200.0, 320, 400, 50,
        &this->font, "High Score", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["AUTHOR_STATE_BTN"] = new Button(app->getSize().x / 2 - 200.0, 380, 400, 50,
        &this->font, "Author", Color(70, 70, 70, 200)
        , Color(100, 100, 100, 255), Color(20, 20, 20, 200));

    this->buttons["GAME_QUIT_BTN"] = new Button(app->getSize().x / 2 - 200.0, 440, 400, 50,
        &this->font, "Exit", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["TEST GAME"] = new Button(app->getSize().x / 2 - 200.0, 500, 400, 50,
        &this->font, "TEST GAME", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}
MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    std::cout << "In MainMenuState::MainMenuState(), line: " << __LINE__ << '\n';
    this->initFonts();
    this->initButtons();
}
MainMenuState ::~MainMenuState()
{
    std::cout << "In MainMenuState::~MainMenuState(), line: " << __LINE__ << '\n';
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}
void MainMenuState::updateKeyBinds()
{
    std::cout << "In MainMenuState::updateKeyBinds(), line: " << __LINE__ << '\n';
    this->checkForQuit();
}
void MainMenuState::endState()
{
    std::cout << "In MainMenuState::endState(), line: " << __LINE__ << '\n';
    cout << "End MainMenu" << endl;
}
bool MainMenuState::checkSaved()
{
    std::cout << "In MainMenuState::checkSaved(), line: " << __LINE__ << '\n';
    ifstream ifs("Save/PreviousBoard.ini");
    int a;
    ifs >> a;
    if (a <= 0)
        return false;
    return true;
}
void MainMenuState::updateButtons()
{
    std::cout << "In MainMenuState::updateButtons(), line: " << __LINE__ << '\n';
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

    if (this->buttons["TEST GAME"]->isPressed())
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
    std::cout << "In MainMenuState::update(), line: " << __LINE__ << '\n';
    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();
    //system("cls") ;
    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;

}
void MainMenuState::renderButtons(RenderTarget* target)
{
    std::cout << "In MainMenuState::renderButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void MainMenuState::render(RenderTarget* target)
{
    std::cout << "In MainMenuState::render(), line: " << __LINE__ << '\n';
    if (!target)
        target = this->app;

    target->draw(this->background);
    this->renderButtons(target);
}

