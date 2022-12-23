
#include "ChooseModeState.h"


void ChooseModeState::initFonts()
{
    std::cout << "In ChooseModeState::initFonts(), line: " << __LINE__ << '\n';
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
    texture.loadFromFile("External/images/mainmenu.jpg");
    this->background.setTexture(texture);
    this->background.setScale(4.f, 4.f);
}
void ChooseModeState::initButtons()
{
    std::cout << "In ChooseModeState::initButtons(), line: " << __LINE__ << '\n';
    this->buttons["EASY_STATE"] = new Button(app->getSize().x / 2 - 200.0, 260, 400, 50,
        &this->font, "EASY", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["MEDIUM_STATE"] = new Button(app->getSize().x / 2 - 200.0, 320, 400, 50,
        &this->font, "MEDIUM", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["HARD_STATE"] = new Button(app->getSize().x / 2 - 200.0, 380, 400, 50,
        &this->font, "HARD", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["BACK_TO_MENU_STATE"] = new Button(app->getSize().x / 2 - 200.0, 440, 400, 50,
        &this->font, "Back to Menu", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}
ChooseModeState::ChooseModeState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    std::cout << "In ChooseModeState::ChooseModeState(), line: " << __LINE__ << '\n';
    this->initFonts();
    this->initButtons();

}

ChooseModeState ::~ChooseModeState()
{
    std::cout << "In ChooseModeState::~ChooseModeState(), line: " << __LINE__ << '\n';
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}
void ChooseModeState::updateKeyBinds()
{
    std::cout << "In ChooseModeState::updateKeyBinds(), line: " << __LINE__ << '\n';
    this->checkForQuit();
}
void ChooseModeState::endState()
{
    std::cout << "In ChooseModeState::endState(), line: " << __LINE__ << '\n';
    cout << "End MainMenu" << endl;
}
void ChooseModeState::updateButtons()
{
    std::cout << "In ChooseModeState::updateButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
   
    // mode , saved 
    // 0 : easy , 1 : medium , 2 : hard 

    if (this->buttons["EASY_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->app , this->states , 0 ,  0 )) ;
    }

    if (this->buttons["MEDIUM_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->app, this->states, 1, 0));
    }

    if (this->buttons["HARD_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->app, this->states, 2, 0));
    }

    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->quit = true;
    }
}

void ChooseModeState::update()
{
    std::cout << "In ChooseModeState::update(), line: " << __LINE__ << '\n';
    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();

    //system("cls") ;
    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;

}
void ChooseModeState::renderButtons(RenderTarget* target)
{
    std::cout << "In ChooseModeState::renderButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void ChooseModeState::render(RenderTarget* target)
{
    std::cout << "In ChooseModeState::render(), line: " << __LINE__ << '\n';
    if (!target)
        target = this->app;
    target->draw(this->background);
    this->renderButtons(target);
}

