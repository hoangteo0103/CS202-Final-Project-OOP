
#include "LoseState.h"
void LoseState::initFonts()
{
    std::cout << "In LoseState::initFonts(), line: " << __LINE__ << '\n';
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
}
void LoseState::initButtons(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    std::cout << "In LoseState::initButtons(), line: " << __LINE__ << '\n';
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
            static_cast<float> (app.getSize().x) /2.f,
            static_cast<float> (app.getSize().y) / 1.5f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(
        background.getPosition().x + app.getSize().x / 2 - this->container.getSize().x / 2.f, background.getPosition().y + app.getSize().y / 2 - this->container.getSize().y / 2.f);
    // Init buttons
    
    this->buttons["OK"] = new Button(background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 25.0, 400, 75,
        &this->font, "OK", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    
    // Init Text
    this->menutext.setFont(font);
    this->menutext.setFillColor(Color(255, 255, 255, 200));
    this->menutext.setCharacterSize(35);
    this->menutext.setString("You lose. Lucky next time");
    this->menutext.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 20.f);
}
void LoseState::initState(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    std::cout << "In LoseState::initState(), line: " << __LINE__ << '\n';
    this->initFonts();
    this->initButtons(app, player, map);
}
LoseState::LoseState()
{
    std::cout << "In LoseState::LoseState(), line: " << __LINE__ << '\n';
}

LoseState::~LoseState()
{
    std::cout << "In LoseState::~LoseState(), line: " << __LINE__ << '\n';
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->ok = false;
}
const bool& LoseState::getOk() const
{
    std::cout << "In LoseState::getOk(), line: " << __LINE__ << '\n';
    return this->ok;
}
void LoseState::updateMousePositions(Vector2f mousePosView)
{
    std::cout << "In LoseState::updateMousePositions(), line: " << __LINE__ << '\n';
    this->mousePosView = mousePosView;
}
void LoseState::updateButtons()
{
    std::cout << "In LoseState::updateButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}
void LoseState::update()
{
    std::cout << "In LoseState::update(), line: " << __LINE__ << '\n';
    this->updateButtons();

    if (this->buttons["OK"]->isPressed())
    {
        this->ok = true;
    }
}

void LoseState::renderButtons(RenderTarget* target)
{
    std::cout << "In LoseState::renderButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void LoseState::render(RenderTarget* target)
{
    std::cout << "In LoseState::render(), line: " << __LINE__ << '\n';
    target->draw(background);
    target->draw(container);
    target->draw(menutext);
    this->renderButtons(target);
}
