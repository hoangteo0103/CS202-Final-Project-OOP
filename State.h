#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio/Music.hpp>
#include <time.h>
#include<iostream>
#include<stack>

using namespace sf;
using namespace std;
class State
{
protected:
    stack<State*>* states;
    RenderWindow* app;
    bool paused;
    bool quit;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

public:
    State(RenderWindow* app, stack<State*>* states);
    virtual ~State();
    // Functions
    void pauseState();
    void unpauseState();
    const bool& getQuit() const;
    //virtual void checkForQuit();
    //virtual void updateKeyBinds() = 0;
    virtual void updateMousePositions();
    virtual void endState() = 0;
    virtual void update() = 0;
    virtual void render(RenderTarget* target = nullptr) = 0;

};
#endif
