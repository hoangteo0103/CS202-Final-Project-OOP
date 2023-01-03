#include "WinState.h"

void WinState::initButtons(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->ok = false;
   
    //Init background
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
            static_cast<float> (app.getSize().y) / 1.5f));
    this->texture.loadFromFile("External/images/win_menu.png");
    this->container.setTexture(&this->texture);
    this->container.setPosition(
        background.getPosition().x + app.getSize().x / 2 - this->container.getSize().x / 2.f, background.getPosition().y + app.getSize().y / 2 - this->container.getSize().y / 2.f);
    
    // Init buttons
    this->buttons["OK"] = new Button("External/texture", background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 10.0, 400, 100, "ok_button", "sound/main_menu/hover.ogg", "sound/main_menu/active.ogg");
}

void WinState::initState(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->initButtons(app, player, map);
}

WinState::WinState() : ok(false)
{
}

WinState::~WinState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->ok = false;
}

const bool& WinState::getOk() const
{
    return this->ok;
}

void WinState::updateMousePositions(Vector2f mousePosView)
{
    this->mousePosView = mousePosView;
}

void WinState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void WinState::update()
{
    this->updateButtons();

    if (this->buttons["OK"]->isPressed())
    {
        this->ok = true;
    }
}

void WinState::hide()
{
    Vector2f des(0.f - this->background.getSize().x, 0.f);
    Vector2f dis = this->background.getPosition() - des;
    this->background.move(dis);
    this->container.move(dis);
    for (auto& it : this->buttons)
    {
        it.second->move(dis);
    }
}

void WinState::renderButtons(RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void WinState::render(RenderTarget* target)
{
    target->draw(background);
    target->draw(container);
    this->renderButtons(target);
}