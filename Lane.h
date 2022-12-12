#pragma once
#include "COBSTACLE.h"
#include "CTRAFFICLIGHT.h"


class Lane
{
private :
	vector<COBSTACLE*> obstacle;
	vector<CTRAFFICLIGHT> lights; 
	int num; 
public :
	
	Lane(int typeObstacle ,int dir,int num, float speed, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void move(float delta_time);
	void render(RenderTarget* target);


	friend class CPEOPLE;
};

