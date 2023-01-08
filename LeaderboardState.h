#pragma once
#include "GameState.h"
#include "State.h"
#include "Button.h"

class LeaderboardState :
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
    void initBackground();
    void initButtons();
    void initSounds();
    void initBeginner();
    void initIntermediate();
    void initExpert();

public:
    LeaderboardState(RenderWindow* app, stack<State*>* states);
    virtual ~LeaderboardState();
    // Functions

    // Update
    void endState();
    void updateButtons();
    void update();

    // Render
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);
};
