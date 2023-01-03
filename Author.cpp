#include "Author.h"

void Author::initBackground()
{
    texture.loadFromFile("External/images/author.png");
    this->background.setTexture(texture);
}

void Author::initButtons()
{
    this->buttons["BACK_TO_MENU_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 570, 400, 50, "back_to_menu_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");

}

void Author::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Load_game.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}

Author::Author(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{   
    this->initBackground();
    this->initButtons();
    this->initSounds();
}

Author ::~Author()
{
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->theme.stop();
}

void Author::endState()
{

}

void Author::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new MainMenuState(this->app, this->states));
    }
}

void Author::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void Author::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void Author::render(RenderTarget* target)
{
    if (!target)
        target = this->app;
    target->draw(this->background);
    this->renderButtons(target);
}