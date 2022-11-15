#ifndef ChooseModeState_H
#define ChooseModeState_H
#include "Base.h"
#include "GameState.h"

class ChooseModeState :
    public State
{
private:
    map<string, Button* > buttons;
    Font font;
    Texture texture;
    Sprite background;
    void initFonts();
    void initButtons();

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
#endif


