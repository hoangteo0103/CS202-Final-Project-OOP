#pragma once
#include "Lane.h"
#include "Base.h"
#include <random>

const vector<string> OBSTACLETEXTUREPATH = { "asset\\obstacle\\obstacle0.png" }; // "asset\\road\\road1.png", "asset\\road\\road2.png", "asset\\road\\road3.png" };
const vector<int> SIZEOBSTACLE = { 59 }; // "asset\\road\\road1.png", "asset\\road\\road2.png", "asset\\road\\road3.png" };


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

