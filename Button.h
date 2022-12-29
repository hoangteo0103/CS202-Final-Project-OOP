#ifndef BUTTON_H
#define BUTTON_H
#include "Base.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include<iostream>
#include<fstream>
#include "SoundEffect.h"

using namespace sf;
using namespace std;
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
class Button
{
private:
    short unsigned buttonState;
    RectangleShape shape;
    string name;
    string path;

    Texture idleTexture;
    Texture hoverTexture;
    SoundEffect hover, active;


public:
    Button(string path, float x, float y, float width, float height, string name, string hover, string active);
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