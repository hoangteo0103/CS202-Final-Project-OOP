#pragma once
#include "GameState.h"
#include "State.h"
#include "Button.h"

class Instruction :
    public State
{
private:
    map<string, Button* > buttons;
    Texture texture;
    Sprite background;
    Music theme;
    int stage_count;

private:
    void initBackground();
    void initButtons();
    void initSounds();

public:
    Instruction(RenderWindow* app, stack<State*>* states);
    virtual ~Instruction();
    // Functions

    // Update
    void endState();
    void updateButtons();
    void updateInstructions();
    void update();

    // Render
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);
};