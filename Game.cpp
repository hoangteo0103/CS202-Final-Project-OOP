#include "Game.h"
#include "MainMenuState.h"
using namespace std;
using namespace sf;
//Static Functions

//Initialize functions
void Game::initWindow()
{
    std::cout << "In Game::initWindow(), line: " << __LINE__ << '\n';
    ifstream ifs("Data/window.ini");
    string title = "CROSSY ROAD";

    VideoMode Size(1280, 720);
    this->app = new RenderWindow(Size, title);
}
void Game::initStates()
{
    std::cout << "In Game::initStates(), line: " << __LINE__ << '\n';
    this->states.push(new MainMenuState(this->app, &this->states));
}

// Constructor functions
Game::Game()
{
    std::cout << "In Game::Game(), line: " << __LINE__ << '\n';
    this->initWindow();
    this->initStates();
}
Game::~Game()
{
    std::cout << "In Game::~Game(), line: " << __LINE__ << '\n';
    delete this->app;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }

}
void Game::endApplication()
{
    std::cout << "In Game::endApplication(), line: " << __LINE__ << '\n';
    cout << "Ending application" << endl;
}
void Game::updateSFMLEvents()
{
    std::cout << "In Game::updateSFMLEvents(), line: " << __LINE__ << '\n';
    while (this->app->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == Event::Closed)
            this->app->close();
    }
}
void Game::update()
{
    std::cout << "In Game::update(), line: " << __LINE__ << '\n';
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update();
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();

            delete this->states.top();
            this->states.pop();

        }
    }
}
void Game::render()
{
    std::cout << "In Game::render(), line: " << __LINE__ << '\n';
    this->app->clear();
    if (!this->states.empty())
        this->states.top()->render();
    else
    {

        this->endApplication();
        this->app->close();
    }
    this->app->display();
}
void Game::run()
{
    std::cout << "In Game::run(), line: " << __LINE__ << '\n';
    while (this->app->isOpen())
    {
        this->update();
        this->render();
    }
}
