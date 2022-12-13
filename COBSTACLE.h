#pragma once
#include "Base.h"
class COBSTACLE : public Object
{
private: 
	int direction; 
public :
	COBSTACLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos, int dir);
	void setSpeed(int s)
	{
		this->speed = s;
	}
	void move(float delta_time);
};

