#include "Button.h"

Button::Button(string path, float x, float y, float width, float height, string name, string hover, string active)
{
    this->path = path;
    this->name = name;
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(Vector2f(x, y));
    this->shape.setSize(Vector2f(width, height));
    if (!this->idleTexture.loadFromFile(this->path + "/" + this->name + "/" + this->name + "_idle.png"));
    {
    }
    if (!this->hoverTexture.loadFromFile(this->path + "/" + this->name + "/" + this->name + "_hover.png"));
    {
    }
    this->hover.init(hover);
    this->active.init(active);
}

Button::~Button()
{
}
void Button::setOutline(Color  color)
{
    this->shape.setOutlineThickness(1.0f);
    this->shape.setOutlineColor(color);
}

void Button::update(const Vector2f mousePos)
{
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
        this->hover.play();
        this->shape.setTexture(&this->idleTexture);
        break;
    case BTN_HOVER:
        this->shape.setTexture(&this->hoverTexture);
        break;
    case BTN_ACTIVE:
        this->active.play();
        //this->shape.setFillColor(this->activeColor);
        break;
    default:
        //this->shape.setFillColor(Color::Red);
        break;
    }
}

const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}
void Button::render(RenderTarget* target)
{
    target->draw(this->shape);
}

void Button::move(const Vector2f distance)
{
    this->shape.move(distance);
}

void Button::setPosition(const Vector2f pos)
{
    this->shape.setPosition(pos);

}

void Button::setTexture(string path)
{
    if (!this->idleTexture.loadFromFile(path + "_button_idle.png"));
    {
    }
    if (!this->hoverTexture.loadFromFile(path + "_button_hover.png"));
    {
    }
}