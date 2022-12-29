#pragma once
#include "GameState.h"
#include "State.h"
#include "Button.h"

class ChooseModeState :
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
    ChooseModeState(RenderWindow* app, stack<State*>* states);
    virtual ~ChooseModeState();
    // Functions
    void updateKeyBinds();
    void updateButtons();
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};



