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


//class Mouvment
//{
//public:
//    Mouvment() {};
//
//    void goDirection(const int& dir, sf::Sprite& spritesheet)
//    {
//        switch (dir) {
//        case 0:
//            spritesheet.move(sf::Vector2f(0, -3));
//            break;
//        case 1:
//            spritesheet.move(sf::Vector2f(0, 3));
//            break;
//        case 2:
//            spritesheet.move(sf::Vector2f(3, 0));
//            break;
//        case 3:
//            spritesheet.move(sf::Vector2f(-3, 0));
//            break;
//        }
//    }
//};
#include "Game.h"
using namespace sf;
int main()
{
    //srand(time(0));
////Game game;
////game.run();
////return 0;
//sf::RenderWindow _window(sf::VideoMode(600, 600), "Hello World");
//sf::Texture _texture;
//sf::Vector2i source(DIRECTION_X_DOWN_INITAL, DIRECTION_Y_DOWN_INITAL);
//
//Mouvment mouvment;
//if (!(_texture.loadFromFile("rex.png")))
//{
//    cout << "Could Not Load File.." << endl;
//}
//
//sf::Sprite _sprite;
//_sprite.setTexture(_texture);
//
//_sprite.setTextureRect(sf::IntRect(sf::Vector2i(source.x * 50, source.y * 50), sf::Vector2i(50, 50)));
//
//while (_window.isOpen())
//{
//    sf::Event _event;
//    while (_window.pollEvent(_event))
//    {
//        switch (_event.type)
//        {
//        case sf::Event::Closed:
//            _window.close();
//            exit(1);
//        case sf::Event::KeyPressed:
//            switch (_event.key.code)
//            {
//            case sf::Keyboard::Right:
//                mouvment.goDirection(2, _sprite);
//                source.x = DIRECTION_X_RIGHT_INITAL;
//                source.y = DIRECTION_Y_RIGHT_INITAL;
//                break;
//            case sf::Keyboard::Left:
//                mouvment.goDirection(3, _sprite);
//                source.x = DIRECTION_X_LEFT_INITAL;
//                source.y = DIRETION_Y_LEFT_INITAL;
//                break;
//            case sf::Keyboard::Up:
//                mouvment.goDirection(0, _sprite);
//                source.x = DIRECTION_X_UP_INITAL;
//                source.y = DIRECTION_Y_UP_INITAL;
//                break;
//            case sf::Keyboard::Down:
//                mouvment.goDirection(1, _sprite);
//                source.x = DIRECTION_X_DOWN_INITAL;
//                source.y = DIRECTION_Y_DOWN_INITAL;
//                break;
//            }
//            break;
//        }
//    }
//    _sprite.setTextureRect(sf::IntRect(source.x * SPRITE_WIDTH, source.y * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT));
//    _window.draw(_sprite);
//    _window.display();
//    _window.clear();
//}

    sf::RenderWindow _window(sf::VideoMode(600, 600), "Hello World");
    
    sf::Texture _texture;
    if (!(_texture.loadFromFile("rex.png")))
    {
        cout << "Could Not Load File.." << endl;
    }
    CPEOPLE player(&_texture, sf::Vector2u(4, 4), 0.3f, 100.0f);


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




