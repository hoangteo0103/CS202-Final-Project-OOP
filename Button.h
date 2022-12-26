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
    string name;
    string path;

    Texture idleTexture;
    Texture hoverTexture;

public:
    /*Button(float x, float y, float width, float height, Font* font,
        string text, Color idleColor, Color hoverColor, Color activeColor);*/
    Button(string path, float x, float y, float width, float height, string name);
    ~Button();
    const bool isPressed() const;
    virtual void setOutline(Color color);
    void update(const Vector2f mousePos);
    void render(RenderTarget* target);
    void move(const Vector2f distance);
    void setPosition(const Vector2f pos);
    void setTexture(string path);
};
#endif // BUTTON_H