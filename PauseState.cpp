#include "PauseState.h"
void PauseState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
}
void PauseState::initState(RenderWindow& app, CPEOPLE* player)
{
    this->initFonts();
    this->resume = false;
    //Init background
    this->background.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x),
            static_cast<float> (app.getSize().y)));
    this->background.setFillColor(Color(20, 20, 20, 100));
    this->background.setPosition(player->getPosition().x - app.getSize().x/2, player->getPosition().y - app.getSize().y/2);
    // Init container
    this->container.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x) / 2.f,
            static_cast<float> (app.getSize().y) / 1.5f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(player->getPosition().x - this->container.getSize().x / 2.f, player->getPosition().y - this->container.getSize().y/2.f);
    // Init buttons
    this->buttons["RESUME"] = new Button(player->getPosition().x - 200.0, player->getPosition().y - 125.0, 400, 75,
        &this->font, "RESUME", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["RESTART"] = new Button(player->getPosition().x - 200.0, player->getPosition().y - 25.0, 400, 75,
        &this->font, "RESTART", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["EXIT"] = new Button(player->getPosition().x - 200.0, player->getPosition().y + 75.0, 400, 75,
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
}
const bool& PauseState::getResume() const
{
    return this->resume;
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
}

void PauseState::render(RenderTarget& target)
{
    target.draw(background);
    target.draw(container);
    target.draw(menutext);
    for (auto& i : this->buttons)
    {
        i.second->render(&target);
    }
}