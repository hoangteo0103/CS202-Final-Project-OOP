
#include "LoseState.h"
void LoseState::initFonts()
{
    if (!this->font.loadFromFile("External/font/Contb.ttf"))
    {

    }
}
void LoseState::initState(RenderWindow& app)
{
    this->initFonts();
    this->ok = false;
    //Init background
    this->background.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x),
            static_cast<float> (app.getSize().y)));
    this->background.setFillColor(Color(30, 20, 20, 100));
    // Init container
    this->container.setSize(
        Vector2f(
            static_cast<float> (app.getSize().x) - 50.f,
            static_cast<float> (app.getSize().y) / 4.f));
    this->container.setFillColor(Color::Black);
    this->container.setPosition(
        Vector2f(15.f, static_cast<float>(app.getSize().y) / 2.f - this->container.getSize().y / 2.f));
    // Init buttons
    this->buttons["OK"] = new Button(520, 350, 200, 50,
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
LoseState::LoseState()
{
}

LoseState::~LoseState()
{

    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->ok = false;
}
const bool& LoseState::getOk() const
{
    return this->ok;
}
void LoseState::updateMousePositions(Vector2f mousePosView)
{
    this->mousePosView = mousePosView;
}
void LoseState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}
void LoseState::update()
{
    this->updateButtons();

    if (this->buttons["OK"]->isPressed())
    {
        this->ok = true;
    }
}

void LoseState::render(RenderTarget& target)
{
    target.draw(background);
    target.draw(container);

    target.draw(menutext);
    for (auto& i : this->buttons)
    {
        i.second->render(&target);
    }
}
