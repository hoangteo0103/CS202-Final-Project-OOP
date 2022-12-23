#include "PlayAgainState.h"
void PlayAgainState::initFonts()
{
    std::cout << "In PlayAgainState::initFonts(), line: " << __LINE__ << '\n';
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
}

void PlayAgainState::initButtons(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    std::cout << "In PlayAgainState::initButtons(), line: " << __LINE__ << '\n';
    this->Yes = false;
    this->No = false;
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
            static_cast<float> (app.getSize().x)/2.f,
            static_cast<float> (app.getSize().y) / 1.5f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(background.getPosition().x + app.getSize().x / 2 - this->container.getSize().x / 2.f, background.getPosition().y + app.getSize().y / 2 - this->container.getSize().y / 2.f);
    // Init buttons
    this->buttons["YES"] = new Button(background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 - 75.0, 400, 75,
        &this->font, "YES", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["NO"] = new Button(background.getPosition().x + app.getSize().x / 2 - 200.0, background.getPosition().y + app.getSize().y / 2 + 25.0, 400, 75,
        &this->font, "NO", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    // Init Text
    this->menutext.setFont(font);
    this->menutext.setFillColor(Color(255, 255, 255, 200));
    this->menutext.setCharacterSize(40);
    this->menutext.setString("Do you want to play again ?");
    this->menutext.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 20.f);
}


void PlayAgainState::initState(RenderWindow& app, CPEOPLE* player, CMap* map)
{
    std::cout << "In PlayAgainState::initState(), line: " << __LINE__ << '\n';
    this->initFonts();
    this->initButtons(app,player,map);
}
PlayAgainState::PlayAgainState()
{
    std::cout << "In PlayAgainState::PlayAgainState(), line: " << __LINE__ << '\n';
}

PlayAgainState::~PlayAgainState()
{
    std::cout << "In PlayAgainState::~PlayAgainState(), line: " << __LINE__ << '\n';
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->Yes = false;
    this->No = false;
}
const bool& PlayAgainState::getYes() const
{
    std::cout << "In PlayAgainState::getYes(), line: " << __LINE__ << '\n';
    return this->Yes;
}
const bool& PlayAgainState::getNo() const
{
    std::cout << "In PlayAgainState::getNo(), line: " << __LINE__ << '\n';
    return this->No;
}
void PlayAgainState::updateMousePositions(Vector2f mousePosView)
{
    std::cout << "In PlayAgainState::updateMousePositions(), line: " << __LINE__ << '\n';
    this->mousePosView = mousePosView;
}
void PlayAgainState::updateButtons()
{
    std::cout << "In PlayAgainState::updateButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}
void PlayAgainState::update()
{
    std::cout << "In PlayAgainState::update(), line: " << __LINE__ << '\n';
    this->updateButtons();
    if (this->buttons["YES"]->isPressed())
    {
        this->Yes = true;
    }
    if (this->buttons["NO"]->isPressed())
    {
        this->No = true;
    }
}

void PlayAgainState::renderButtons(RenderTarget* target)
{
    std::cout << "In PlayAgainState::renderButtons(), line: " << __LINE__ << '\n';
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void PlayAgainState::render(RenderTarget* target)
{
    std::cout << "In PlayAgainState::render(), line: " << __LINE__ << '\n';
    target->draw(background);
    target->draw(container);
    target->draw(menutext);
    this->renderButtons(target);
}
