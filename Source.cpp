#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
#include "CPEOPLE.h"

#define SPRITE_WIDTH 47
#define SPRITE_HEIGHT 62
#define DIRECTION_Y_DOWN_INITAL 0
#define DIRETION_Y_LEFT_INITAL 1
#define DIRECTION_Y_RIGHT_INITAL 2
#define DIRECTION_Y_UP_INITAL 3

#define DIRECTION_X_DOWN_INITAL 0
#define DIRECTION_X_LEFT_INITAL 0
#define DIRECTION_X_RIGHT_INITAL 0
#define DIRECTION_X_UP_INITAL 0


using std::cout;
using std::endl;

#include "Game.h"
using namespace sf;
int main()
{
    sf::RenderWindow _window(sf::VideoMode(600, 600), "Hello World");
   
    CPEOPLE player("rex.png", sf::Vector2u(4, 4), 0.3f, 100.0f);


    sf::Clock clock;

    float delta_time = 0.0f;

    while (_window.isOpen())
    {
        sf::Event _event;
        delta_time = clock.restart().asSeconds();

        while (_window.pollEvent(_event))
        {
            switch (_event.type)
            {
            case sf::Event::Closed:
                _window.close();
                break;
            }
        }

        player.move(delta_time);


        _window.clear();
        player.draw(_window);
        _window.display();
    }
}




