#pragma once
#include "GameState.h"
#include "State.h"
#include "Button.h"

class Author :
    public State
{
private:
    map<string, Button* > buttons;
    Font font;
    Texture texture;
    Sprite background;
    Music theme;

private:
    void initFonts();
    void initButtons();
    void initSounds();

public:
    Author(RenderWindow* app, stack<State*>* states);
    virtual ~Author();
    // Functions
    void updateKeyBinds();
    void updateButtons();
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};



