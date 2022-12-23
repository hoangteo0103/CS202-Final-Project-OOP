#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* font,
    string text, Color idleColor, Color hoverColor, Color activeColor)
{
    // std::cout << "In Button::Button(), line: " << __LINE__ << '\n';
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(Vector2f(x, y));
    this->shape.setSize(Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(Color::White);
    this->text.setCharacterSize(16);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 2.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->shape.setFillColor(this->idleColor);
    this->setOutline(Color::Red);
}
Button::~Button()
{
    // std::cout << "In Button::~Button(), line: " << __LINE__ << '\n';
}
void Button::setOutline(Color  color)
{
    // std::cout << "In Button::setOutline(), line: " << __LINE__ << '\n';
    this->shape.setOutlineThickness(1.0f);
    this->shape.setOutlineColor(color);
}

void Button::setTextColor(Color color)
{
    // std::cout << "In Button::setTextColor(), line: " << __LINE__ << '\n';
    this->text.setFillColor(color);
}
void Button::updateText(string t)
{
    // std::cout << "In Button::updateText(), line: " << __LINE__ << '\n';
    this->text.setString(t);
}
void Button::update(const Vector2f mousePos)
{
    // std::cout << "In Button::update(), line: " << __LINE__ << '\n';
    //IDLE
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        //HOVER
        this->buttonState = BTN_HOVER;
        bool leftPress = false;
        while (Mouse::isButtonPressed(Mouse::Left))
        {
            leftPress = true;
        }
        if (leftPress)  this->buttonState = BTN_ACTIVE;
    }
    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(Color::Red);
        break;
    }
}
const bool Button::isPressed() const
{
    // std::cout << "In Button::isPressed(), line: " << __LINE__ << '\n';
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}
void Button::render(RenderTarget* target)
{
    // std::cout << "In Button::render(), line: " << __LINE__ << '\n';
    target->draw(this->shape);
    target->draw(this->text);
}

void Button::move(const Vector2f distance)
{
    // std::cout << "In Button::move(), line: " << __LINE__ << '\n';
    this->shape.move(distance);
    this->text.move(distance);
}

void Button::setPosition(const Vector2f pos)
{
    // std::cout << "In Button::setPosition(), line: " << __LINE__ << '\n';
    this->shape.setPosition(pos);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 2.f
    );
}