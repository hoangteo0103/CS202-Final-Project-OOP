#pragma once
#include "Base.h"
#include "Lane.h"

enum PLAYERSTATE { MOVE = 0, IDLE = 1, DEATH = 2 };

class CPEOPLE : public Object
{
public:
	
	CPEOPLE() {};
	CPEOPLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos);
	void move(float delta_time, const sf::Vector2u map_size);
	void update(float delta_time, const sf::Vector2u map_size);
	bool isCollision(const Lane& lane);
	
private:
	int state;
	int row;
	int face_direction; // 0 - down, 1 - left, 2 - right, 3 - up
};

