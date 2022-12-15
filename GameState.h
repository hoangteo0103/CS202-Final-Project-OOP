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
#include "LanePack.h"
#include "CTRAFFICLIGHT.h"


class GameState :
    public State
{
private:
    PauseState pmenu;
    WinState winState;
    LoseState loseState;
    PlayAgainState againState;

    float delta_time = 0.0f;
    Clock delta_clock;
    //ostringstream ssTime;
    map<string, Button* > buttons;
    Font font;
    Texture texture;
    Sprite background;
    bool isUpdated;
    bool ok;
    bool paused = false;
    CMap map; 
    CPEOPLE *player;
    CView* view;
    LanePack* lane_management;

    sf::Vector2f starting_position;
    int current_level;
    int win_line_y;
    int previousTime;
    void initFonts();
    //void initButtons();

public:
    GameState(RenderWindow* app, stack<State*>* states, bool saved);
    virtual ~GameState();
    // Functions
    void Reset(int level = 1);
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
    void endGame();
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);
    void updateMovingButton(Vector2f& distance);
};
#endif

