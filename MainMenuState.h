#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "ChooseModeState.h"
#include "GameState.h"
#include "SoundEffect.h"
#include "Author.h"
#include "Instruction.h"
class MainMenuState :
    public State
{
private:
    Texture texture;
    Sprite background;
    map<string, Button* > buttons;
    Music theme;

private:
    void initBackground();
    void initButtons();
    void initSounds();

public:
    MainMenuState(RenderWindow* app, stack<State*>* states);
    virtual ~MainMenuState();
    // Functions

    bool checkSaved();
    // Update
    void endState();
    void updateButtons();
    void update();

    // Render
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);
};

#endif // MAINMENUSTATE_H


