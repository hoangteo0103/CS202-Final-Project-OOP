#ifndef GameState_H
#define GameState_H
#include "Base.h"
#include "PauseState.h"
#include "WinState.h"
#include "LoseState.h"
#include "PlayAgainState.h"

#include "CPEOPLE.h"
#include "COBSTACLE.h"
#include "CView.h"
#include "Lane.h"


class GameState :
    public State
{
private:
    //PauseState pausemenu;
    //WinState winState;
    LoseState loseState;
    PlayAgainState againState;
    st::Timer clock;
    Time t;
    Text lblTime;
    //ostringstream ssTime;
    map<string, Button* > buttons;
    Font font;
    Texture texture;
    Sprite background;
    bool isUpdated;
    bool ok;
    CMap map; 
    


    CPEOPLE player; 
    // ("girl.png", sf::Vector2u(6, 9), 0.1f, 300.0f, Vector2f(map.getSize().x / 2, map.getSize().y - 500));
    CView _view; 

    int previousTime;
    void initFonts();
    void initButtons();

public:
    GameState(RenderWindow* app, stack<State*>* states, bool saved);
    virtual ~GameState();
    // Functions
    void Reset();
    void updatePaused();
    void updateKeyBinds();
    void updateBeginner(int time_now);
    void updateIntermediate(int time_now);
    void updateExpert(int time_now);
    void updateLeaderBoard();
    void updateButtons();
    void updateWinState();
    void updateLoseState();
    const bool& getLose() const;
    const bool& getWin() const;
    void endState();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

};
#endif

