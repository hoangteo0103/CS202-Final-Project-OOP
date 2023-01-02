#include "State.h"
using namespace std;
using namespace sf;
State::State(RenderWindow* app, stack<State*>* states)
{
    this->app = app;
    this->states = states;
    this->quit = false;
    this->paused = false;
}
State::~State()
{
}
void State::pauseState() {
    this->paused = true;

}
void State::unpauseState() {
    this->paused = false;

}
void State::updateMousePositions()
{
    this->mousePosWindow = Mouse::getPosition(*this->app);
    this->mousePosView = this->app->mapPixelToCoords(Mouse::getPosition(*this->app));
}
const bool& State::getQuit() const
{
    return this->quit;
}
//void State::checkForQuit()
//{
//    if (Keyboard::isKeyPressed(Keyboard::Escape))
//    {
//        this->quit = true;
//    }
//}
 