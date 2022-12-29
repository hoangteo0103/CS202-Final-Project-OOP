
#include "ChooseModeState.h"


void ChooseModeState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
    texture.loadFromFile("External/images/mainmenu.jpg");
    this->background.setTexture(texture);
    this->background.setScale(4.f, 4.f);
}
void ChooseModeState::initButtons()
{

    this->buttons["EASY_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 260, 400, 50, "easy_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["MEDIUM_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 320, 400, 50, "medium_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["HARD_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 380, 400, 50, "hard_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["BACK_TO_MENU_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 440, 400, 50, "back_to_menu_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");

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
    this->initButtons();
    this->initFonts();
    this->initSounds();
}

ChooseModeState ::~ChooseModeState()
{
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
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

