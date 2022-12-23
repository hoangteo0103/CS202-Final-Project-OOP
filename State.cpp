#include "State.h"
using namespace std;
using namespace sf;
State::State(RenderWindow* app, stack<State*>* states)
{
    std::cout << "In State::State(), line: " << __LINE__ << '\n';
    this->app = app;
    this->states = states;
    this->quit = false;
    this->paused = false;
}
State::~State()
{
    std::cout << "In State::~State(), line: " << __LINE__ << '\n';
}
void State::pauseState() {
    std::cout << "In State::pauseState(), line: " << __LINE__ << '\n';
    this->paused = true;

}
void State::unpauseState() {
    std::cout << "In State::unpauseState(), line: " << __LINE__ << '\n';
    this->paused = false;

}
void State::updateMousePositions()
{
    std::cout << "In State::updateMousePositions(), line: " << __LINE__ << '\n';
    this->mousePosWindow = Mouse::getPosition(*this->app);
    this->mousePosView = this->app->mapPixelToCoords(Mouse::getPosition(*this->app));
}
const bool& State::getQuit() const
{
    std::cout << "In State::getQuit(), line: " << __LINE__ << '\n';
    return this->quit;
}
void State::checkForQuit()
{
    std::cout << "In State::checkForQuit(), line: " << __LINE__ << '\n';
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        this->quit = true;
    }
}
