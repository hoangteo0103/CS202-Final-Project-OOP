#include "PauseState.h"
void PauseState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
}

void PauseState::initButtons(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->resume = false;
    this->restart = false;
    this->exit = false;

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
            static_cast<float> (app.getSize().y) / 1.5f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(background.getPosition().x + app.getSize().x / 2 - this->container.getSize().x / 2.f, background.getPosition().y + app.getSize().y / 2 - this->container.getSize().y / 2.f);
    // Init buttons
    this->buttons["RESUME"] = new Button(background.getPosition().x + app.getSize().x/2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 150.0, 400, 100,
        &this->font, "RESUME", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["RESTART"] = new Button(background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 25.0, 400, 100,
        &this->font, "RESTART", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["EXIT"] = new Button(background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 + 100.0, 400, 100,
        &this->font, "EXIT", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    // Init Text
    this->menutext.setFont(font);
    this->menutext.setFillColor(Color(255, 255, 255, 200));
    this->menutext.setCharacterSize(40);
    this->menutext.setString("PAUSED");
    this->menutext.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 20.f);
}

void PauseState::initState(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    this->initFonts();
    this->initButtons(app, player, map);
}
PauseState::PauseState()
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
    this->restart = false;
    this->exit = false;
}
const bool& PauseState::getResume() const
{
    return this->resume;
}

const bool& PauseState::getRestart() const
{
    return this->restart;
}

const bool& PauseState::getExit() const
{
    return this->exit;
}

void PauseState::Reset()
{
    this->resume = false;
    this->restart = false;
    this->exit = false;
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
    if (this->buttons["RESTART"]->isPressed())
    {
        this->restart = true;
    }
    if (this->buttons["EXIT"]->isPressed())
    {
        this->exit = true;
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
    target->draw(menutext);
    this->renderButtons(target);

}