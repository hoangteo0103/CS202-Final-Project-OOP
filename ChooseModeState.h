#pragma once
#include "GameState.h"
#include "State.h"
#include "Button.h"

class ChooseModeState :
    public State
{
private:
    map<string, Button* > buttons;
    Texture texture;
    Sprite background;
    Music theme;

private:
    void initBackground();
    void initButtons();
    void initSounds();

public:
    ChooseModeState(RenderWindow* app, stack<State*>* states);
    virtual ~ChooseModeState();
    // Functions
    
    // Update
    void endState();
    void updateButtons();
    void update();

    // Render
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};



