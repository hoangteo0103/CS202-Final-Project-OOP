#pragma once
#include "GameState.h"
#include "Button.h"
#include "State.h"
class ModSkinState :
    public State
{
private:
    map<string, Button* > buttons;
    Texture texture;
    Sprite background;
    Music theme;
    RectangleShape container;

private:
    void initBackground();
    void initButtons();
    void initSounds();

public:
    ModSkinState(RenderWindow* app, stack<State*>* states, int mode);
    virtual ~ModSkinState();
    // Functions

    // Update
    void endState();
    void updateButtons();
    void update();

    // Render
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};
