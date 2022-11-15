#ifndef GAME_H
#define GAME_H
#include "GameState.h"
using namespace sf;
using namespace std;
class Game
{
private:
    //Variables
    RenderWindow* app;
    Event sfEvent;
    stack<State*> states;

    //Initialization
    void initWindow();
    void initStates();
public:
    Game();
    virtual ~Game();
    // Functions
    void endApplication();
    void updateSFMLEvents();
    void update();
    void render();
    void run();

};
#endif
