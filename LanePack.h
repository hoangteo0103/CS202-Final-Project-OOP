#pragma once
#include "Lane.h"
#include "Base.h"
#include <random>


class LanePack
{
private:
	float speed; 
	vector<Lane*> lanes;
	vector<sf::Vector2f> position;
	int distance_factor;
public:
	LanePack(int distance);
	~LanePack();
	void init(int speed , int level, sf::Vector2u map_size, int win_line_y);
	void update(float delta_time);
	void draw(sf::RenderWindow& window);
	void reset(int speed ,int level, sf::Vector2u map_size, int win_line_y);
	int getNumOfLanes();
	friend class CPEOPLE;
};

