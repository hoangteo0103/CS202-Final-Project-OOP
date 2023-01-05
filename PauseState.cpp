#include "PauseState.h"

void PauseState::initButtons(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->resume = false;
    this->save = false;
    this->restart = false;
    this->home = false;

    // Calculate position
    Vector2f pos = player->getPosition();
    Vector2f setPos = pos;
    if (pos.x >= app.getSize().x / 2 && pos.x <= map->getSize().x - app.getSize().x / 2)
        setPos.x = pos.x - app.getSize().x / 2;
    else
    {
        if (pos.x < app.getSize().x / 2) setPos.x = 0;
        if (pos.x > map->getSize().x - app.getSize().x / 2) setPos.x = map->getSize().x - app.getSize().x;
    }
    if (pos.y >= app.getSize().y / 2 && pos.y <= map->getSize().y - app.getSize().y / 2)
        setPos.y = pos.y - app.getSize().y / 2;
    else
    {
        if (pos.y < app.getSize().y / 2) setPos.y = 0;
        if (pos.y > map->getSize().y - app.getSize().y / 2) setPos.y = map->getSize().y - app.getSize().y;
    }

    //Init background
    this->background.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x),
            static_cast<float> (app.getSize().y)));
    this->background.setFillColor(Color(20, 20, 20, 100));
    this->background.setPosition(setPos);

    // Init container
    this->container.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x) / 2.f,
            static_cast<float> (app.getSize().y) / 1.2f));
    this->texture.loadFromFile("External/images/pause_menu.png");
    this->container.setTexture(&this->texture);
    this->container.setPosition(background.getPosition().x + app.getSize().x / 2 - this->container.getSize().x / 2.f, background.getPosition().y + app.getSize().y / 2 - this->container.getSize().y / 2.f);
    
    // Init buttons
    this->buttons["RESUME"] = new Button("External/texture", background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 210.0, 400, 100, "resume_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["SAVE"] = new Button("External/texture", background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 85.0, 400, 100, "save_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
    this->buttons["RESTART"] = new Button("External/texture", background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 + 40.0, 400, 100, "restart_button", "sound/main_menu/hover.ogg", "sound/main_menu/empty.ogg");
    this->buttons["HOME"] = new Button("External/texture", background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 + 165.0, 400, 100, "home_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
}

void PauseState::initState(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->initButtons(app, player, map);
}

PauseState::PauseState(): resume(false), save(false), restart(false), home(false)
{

}

PauseState::~PauseState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->resume = false;
    this->save = false;
    this->restart = false;
    this->home = false;
}

const bool& PauseState::getResume() const
{
    return this->resume;
}

const bool& PauseState::getSave() const
{
    return this->save;
}

const bool& PauseState::getRestart() const
{
    return this->restart;
}

const bool& PauseState::getHome() const
{
    return this->home;
}

void PauseState::Reset()
{
    this->resume = false;
    this->save = false;
    this->restart = false;
    this->home = false;
}

void PauseState::updateMousePositions(Vector2f mousePosView)
{
    this->mousePosView = mousePosView;
}

void PauseState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void PauseState::update()
{
    this->updateButtons();
    if (this->buttons["RESUME"]->isPressed())
    {
        this->resume = true;
    }
    if (this->buttons["SAVE"]->isPressed())
    {
        this->save = true;
    }
    if (this->buttons["RESTART"]->isPressed())
    {
        this->restart = true;
    }
    if (this->buttons["HOME"]->isPressed())
    {
        this->home = true;
    }
}

void PauseState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void PauseState::render(RenderTarget* target)
{
    target->draw(background);
    target->draw(container);
    this->renderButtons(target);
}