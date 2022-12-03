#pragma once
#include "Base.h"


class CPEOPLE : public Object
{
public:
	
	CPEOPLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos);
	void move(float delta_time, const sf::Vector2u map_size);
	//void update(float delta_time);

private:
	
	int row;
	int face_direction; // 0 - down, 1 - left, 2 - right, 3 - up
};

