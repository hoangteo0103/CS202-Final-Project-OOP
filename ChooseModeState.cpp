#include "ChooseModeState.h"

void ChooseModeState::initBackground()
{
    texture.loadFromFile("External/images/mainmenu2.png");
    this->background.setTexture(texture);
}

void ChooseModeState::initButtons()
{
    this->buttons["EASY_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 390, 400, 50, "easy_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["MEDIUM_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 450, 400, 50, "medium_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["HARD_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 510, 400, 50, "hard_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["BACK_TO_MENU_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 570, 400, 50, "back_to_menu_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");

}

void ChooseModeState::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Cloudy_country.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}

ChooseModeState::ChooseModeState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initBackground();
    this->initButtons();
    this->initSounds();
}

ChooseModeState ::~ChooseModeState()
{
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void ChooseModeState::endState()
{

}

void ChooseModeState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
   
    // mode , saved 
    // 0 : easy , 1 : medium , 2 : hard 

    if (this->buttons["EASY_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app , this->states , 0 ,  0 )) ;
    }

    if (this->buttons["MEDIUM_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 1, 0));
    }

    if (this->buttons["HARD_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 2, 0));
    }

    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new MainMenuState(this->app, this->states));
    }
}

void ChooseModeState::update()
{
    this->updateMousePositions();
    this->updateButtons();
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

