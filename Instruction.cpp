#include "Instruction.h"

void Instruction::initBackground()
{
    texture.loadFromFile("External/images/mainmenu1.png");
    this->background.setTexture(texture);
}

void Instruction::initButtons()
{
    this->buttons["NEXT_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 555, 400, 50, "next_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["PREVIOUS_BTN"] = new Button("External/texture", app->getSize().x / 2 - 200.0, app->getSize().y, 400, 50, "previous_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["BACK_TO_MENU_STATE"] = new Button("External/texture", app->getSize().x / 2 - 200.0, 615, 400, 50, "back_to_menu_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
}

void Instruction::initSounds()
{
    if (!this->theme.openFromFile("sound/main_menu/Music_Box_Song.ogg"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(40);
    this->theme.play();
}

Instruction::Instruction(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->stage_count = 1;
    this->initBackground();
    this->initButtons();
    this->initSounds();
}

Instruction::~Instruction()
{
    for (auto& it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->theme.stop();
}

void Instruction::endState()
{

}

void Instruction::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["NEXT_BTN"]->isPressed())
    {

    }

    if (this->buttons["PREVIOUS_BTN"]->isPressed())
    {

    }

    if (this->buttons["BACK_TO_MENU_STATE"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new MainMenuState(this->app, this->states));
    }
}

void Instruction::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void Instruction::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}
void Instruction::render(RenderTarget* target)
{
    if (!target)
        target = this->app;
    target->draw(this->background);
    this->renderButtons(target);
}