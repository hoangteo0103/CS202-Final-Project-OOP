#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include<iostream>
#include<fstream>

using namespace sf;
using namespace std;
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
class Button
{
private:
    short unsigned buttonState;
    bool pressed;
    bool hover;
    RectangleShape shape;
    Font* font;
    Text text;

    Color idleColor;
    Color hoverColor;
    Color activeColor;

public:
    Button(float x, float y, float width, float height, Font* font,
        string text, Color idleColor, Color hoverColor, Color activeColor);
    ~Button();
    const bool isPressed() const;
    void updateText(string t);
    virtual void setOutline(Color color);
    void setTextColor(Color color);
    void update(const Vector2f mousePos);
    void render(RenderTarget* target);
    void move(const Vector2f distance);
};
#endif // BUTTON_H