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
    // Name
    string name;
    string path;

    // Shape
    short unsigned buttonState;
    RectangleShape shape;

    //Texture
    Texture idleTexture;
    Texture hoverTexture;

    // SoundEffect
    SoundEffect hover, active;

public:
    Button(string path, float x, float y, float width, float height, string name, string hover, string active);
    ~Button();

    // Update
    void update(const Vector2f mousePos);
    const bool isPressed() const;

    // Position
    void move(const Vector2f distance);
    void setPosition(const Vector2f pos);

    // Render
    void setTexture(string path);
    void render(RenderTarget* target);
};
#endif // BUTTON_H