#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
#include "CPEOPLE.h"
#include "COBSTACLE.h"
#include "CView.h"

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
   
    CPEOPLE player("rex.png", sf::Vector2u(4, 4), 0.3f, 100.0f , Vector2f(100,100));
    COBSTACLE test("test1.png", sf::Vector2u(8, 1), 0.001f, 10.0f, Vector2f(0,200) ,2);
    sf::Clock clock;

    float delta_time = 0.0f;

    sf::Texture map;
    if (!map.loadFromFile("map.jpg"))
        cout << "Couldn't load map" << endl;
    sf::Sprite smap(map);

    CView _view(sf::Vector2f(600, 600));

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
        test.move(delta_time);
        // ===============================================


        _view.update(_window, player);



        // ==================================================
        _window.clear();
        _window.draw(smap);
        player.draw(_window);
        test.draw(_window);
        if (test.collide(player))
        {
            cout << "DUMB"; 
        }
        cout << "player position x: " << player.getPosition().x << endl;
        _window.display();
    }
}




