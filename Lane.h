#pragma once
#include "COBSTACLE.h"



class Lane
{
private :
	vector<COBSTACLE*> obstacle; 
	int num; 
public :
	Lane(int typeObstacle ,int dir,int num, float speed, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void move(float delta_time);
	void render(RenderTarget* target);
};

