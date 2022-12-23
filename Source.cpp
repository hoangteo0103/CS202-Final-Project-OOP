#include "CPEOPLE.h"
#include "COBSTACLE.h"
#include "CView.h"
#include "Lane.h"

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

    Game game; 
    game.run();




    exit(0); 

    //sf::RenderWindow _window(sf::VideoMode(600, 600), "Hello World");

    //
    ////COBSTACLE test("test1.png", sf::Vector2u(8, 1), 0.001f, 10.0f, Vector2f(0, 200), 2);
    //sf::Clock clock;
    //float delta_time = 0.0f;

    //CMap map("dup_map.png");

    ////Lane testLane(0, 2, 3, 10.f, Vector2f(0,300));

    //CPEOPLE player("girl.png", sf::Vector2u(6, 9), 0.1f, 300.0f, Vector2f(map.getSize().x/2, map.getSize().y-500));
    //CView _view(_window, map.getSize());
    //
    //bool endgame = false;

    //while (_window.isOpen())
    //{
    //    sf::Event _event;
    //    delta_time = clock.restart().asSeconds();



    //    while (_window.pollEvent(_event))
    //    {
    //        switch (_event.type)
    //        {
    //        case sf::Event::Closed:
    //            _window.close();
    //            break;
    //        }
    //    }
    //    


    //     player.update(delta_time, map.getSize());
    //     //test.move(delta_time);
    //     testLane.move(delta_time);



    //     _view.update(_window, player);


    //     _window.clear();

    //     map.draw(_window);

    //     player.draw(_window);
    //     //test.draw(_window);
    //     testLane.draw(_window);
    //     if (player.isCollision(testLane))
    //     {
    //         endgame = true;
    //         cout << "DUMB";
    //     }

    //    //cout << "player position x: " << player.getPosition().x << endl;
    //    _window.display();
    //}
}




