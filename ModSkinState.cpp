#include "ModSkinState.h"

ModSkinState::ModSkinState(RenderWindow* app, stack<State*>* states, int mode)
    :State(app, states)
{
    this->initBackground();
    this->initButtons();
    this->initSounds();
}

void ModSkinState::initBackground()
{
    

}

void ModSkinState::initButtons()
{
    this->buttons["GREEN"] = new Button("External/texture", 0, 0, app->getSize().x/4, app->getSize().y, "green_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
    this->buttons["RED"] = new Button("External/texture", app->getSize().x/4, 0, app->getSize().x / 4, app->getSize().y, "red_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
    this->buttons["ORANGE"] = new Button("External/texture", 2* app->getSize().x / 4, 0, app->getSize().x / 4, app->getSize().y, "orange_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
    this->buttons["BLUE"] = new Button("External/texture", 3* app->getSize().x / 4, 0, app->getSize().x / 4, app->getSize().y, "blue_button", "sound/main_menu/empty.ogg", "sound/main_menu/empty.ogg");
}

void ModSkinState::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Echos.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}


ModSkinState ::~ModSkinState()
{
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void ModSkinState::endState()
{

}

void ModSkinState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    // mode , saved 
    // 0 : easy , 1 : medium , 2 : hard 

    if (this->buttons["GREEN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 0, 0, "asset/skin/green.png"));
    }

    if (this->buttons["RED"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 0, 0, "asset/skin/red.png"));
    }

    if (this->buttons["ORANGE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 0, 0, "asset/skin/orange.png"));
    }

    if (this->buttons["BLUE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states, 2, 0, "asset/skin/blue.png"));
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        this->theme.stop();
        this->states->push(new MainMenuState(this->app, this->states));
    }
}

void ModSkinState::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void ModSkinState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void ModSkinState::render(RenderTarget* target)
{
    if (!target)
        target = this->app;
    target->draw(this->background);
    this->renderButtons(target);
}
