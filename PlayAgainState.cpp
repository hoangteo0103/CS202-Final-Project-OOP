#include "PlayAgainState.h"
void PlayAgainState::initFonts()
{
    if (!this->font.loadFromFile("font/Contb.ttf"))
    {

    }
}
void PlayAgainState::initState(RenderWindow& app)
{
    this->initFonts();
    this->Yes = false;
    this->No = false;
    //Init background
    this->background.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x),
            static_cast<float> (app.getSize().y)));
    this->background.setFillColor(Color(20, 20, 20, 100));
    // Init container
    this->container.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x) - 50.f,
            static_cast<float> (app.getSize().y) / 4.f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(
        Vector2f(15.f, static_cast<float>(app.getSize().y) / 2.f - this->container.getSize().y / 2.f));
    // Init buttons
    this->buttons["YES"] = new Button(425, 360, 200, 50,
        &this->font, "YES", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));
    this->buttons["NO"] = new Button(635, 360, 200, 50,
        &this->font, "NO", Color(70, 70, 70, 200)
        , Color(150, 150, 150, 255), Color(20, 20, 20, 200));

    // Init Text
    this->menutext.setFont(font);
    this->menutext.setFillColor(Color(255, 255, 255, 200));
    this->menutext.setCharacterSize(35);
    this->menutext.setString("Do you want to play again");
    this->menutext.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 20.f);
}
PlayAgainState::PlayAgainState()
{
}

PlayAgainState::~PlayAgainState()
{

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
    return this->Yes;
}
const bool& PlayAgainState::getNo() const
{
    return this->No;
}
void PlayAgainState::updateMousePositions(Vector2f mousePosView)
{
    this->mousePosView = mousePosView;
}
void PlayAgainState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}
void PlayAgainState::update()
{
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

void PlayAgainState::render(RenderTarget& target)
{
    target.draw(background);
    target.draw(container);
    target.draw(menutext);
    for (auto& i : this->buttons)
    {
        i.second->render(&target);
    }
}
