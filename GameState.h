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


class GameState : public State
{
private:
    PauseState pmenu;
    WinState winState;
    LoseState loseState;
    PlayAgainState againState;

    st::Timer clock;
    float delta_time = 0.0f;
    Clock delta_clock;
    //ostringstream ssTime;
    map<string, Button* > buttons;
    Font font;
    Texture texture;
    Sprite background;
    float previous_time = 0.0f; 

    bool isUpdated;
    bool ok;
    bool restart;
    bool resume;
    bool paused = false;
    CMap map; 
    CPEOPLE *player;
    CView* view;
    LanePack* lane_management;

    vector<float> speed = { 200.f , 300.f , 400.f };
    int mode;
    sf::Vector2f starting_position;
    int current_level;
    int win_line_y;
    int distance_between_lane;
    void initFonts();
    //void initButtons();

public:
    GameState(RenderWindow* app, stack<State*>* states,int mode, bool saved);
    virtual ~GameState();
    // Functions
    void Reset(int level = 1);
    void updateKeyBinds();
    void updateBeginner(int time_now);
    void updateIntermediate(int time_now);
    void updateExpert(int time_now);
    void updateLeaderBoard();
    void updateButtons();
    void updateWinState();
    void updateLoseState();

    void updateUnpaused();
    void updatePaused();

    const bool& getLose() const;
    const bool& getWin() const;
    void endState();
    void endGame(); 
    void update();
    void render(RenderTarget* target = NULL);
    void renderButtons(RenderTarget* target = NULL);

    void updateMovingButton(Vector2f& distance);
    void hideButton(bool hide);
    void resetButton();

    const bool& isPassLevel() const;
    void playAgain();
};
#endif

