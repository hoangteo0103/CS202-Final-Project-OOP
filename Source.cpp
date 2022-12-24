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

}




