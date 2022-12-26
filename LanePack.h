#pragma once
#include "Lane.h"
#include "Base.h"
#include <random>

const vector<string> OBSTACLETEXTUREPATH = { "asset\\obstacle\\obstacle0.png" ,  "asset\\obstacle\\obstacle1" , "asset\\obstacle\\obstacle2.png" ,
"asset\\obstacle\\obstacle3.png" , "asset\\obstacle\\obstacle4.png" , "asset\\obstacle\\obstacle5.png"
};
const vector<int> SIZEOBSTACLE = { 118 , 89 , 117 , 84  , 92 , 114  }; // "asset\\road\\road1.png", "asset\\road\\road2.png", "asset\\road\\road3.png" };


class LanePack
{
private:
	float speed; 
	int numberLanes; 
	vector<Lane*> lanes;
	vector<COBSTACLE*> obstacles; 
	vector<Sprite> obstacleSprites;
	vector<int> posObstacles; 
	vector<sf::Vector2f> position;
	int distance_factor;
public:
	LanePack(int distance);
	~LanePack();
	void init(int speed , int level, sf::Vector2u map_size, int win_line_y);
	void update(float delta_time);
	void draw(sf::RenderWindow& window);
	void reset(int speed ,int level, sf::Vector2u map_size, int win_line_y);
	void generateObstacle();
	int getNumOfLanes();
	friend class CPEOPLE;
	friend class Mouvment;
};

