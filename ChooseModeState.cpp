
#include "ChooseModeState.h"


void ChooseModeState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
    //texture.loadFromFile("images/select1.png");
    this->background.setTexture(texture);
}
void ChooseModeState::initButtons()
{
    this->buttons["BACK_TO_MENU_STATE"] = new Button(374, 580, 450, 50,
        &this->font, "Back to Menu", Color(0, 0, 0, 0)
        , Color(10, 10, 10, 10), Color(20, 20, 20, 200));

    this->buttons["EASY_STATE"] = new Button(220, 200, 350, 50,
        &this->font, "EASY", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["MEDIUM_STATE"] = new Button(220, 260, 350, 50,
        &this->font, "MEDIUM", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    this->buttons["HARD_STATE"] = new Button(220, 320, 350, 50,
        &this->font, "HARD", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}
ChooseModeState::ChooseModeState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initFonts();
    this->initButtons();

}

ChooseModeState ::~ChooseModeState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}
void ChooseModeState::updateKeyBinds()
{
    this->checkForQuit();
}
void ChooseModeState::endState()
{
    cout << "End MainMenu" << endl;
}
void ChooseModeState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->quit = true;
    }
    
    if (this->buttons["EASY_STATE"]->isPressed())
    {
        //this->states->push(new GameState(this->app, this->states, 10, 10, 10, 0));
        // this->states->push(new GameState(this->app , this->states , 9 , 9 ,8)) ;
        this->quit = true;
    }

    if (this->buttons["MEDIUM_STATE"]->isPressed())
    {
        //this->states->push(new GameState(this->app, this->states, 16, 16, 40, 0));
        this->quit = true;
    }

    if (this->buttons["HARD_STATE"]->isPressed())
    {
        //this->states->push(new GameState(this->app, this->states, 30, 16, 99, 0));
        this->quit = true;
    }
    
}

void ChooseModeState::update()
{

    this->updateMousePositions();
    this->updateKeyBinds();
    this->updateButtons();

    //system("cls") ;
    //cout << mousePosView.x <<' ' << mousePosView.y <<endl;

}
void ChooseModeState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void ChooseModeState::render(RenderTarget* target)
{
    if (!target)
        target = this->app;
    target->draw(this->background);
    this->renderButtons(target);
}

