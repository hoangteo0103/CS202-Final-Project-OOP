#pragma once
#include "COBSTACLE.h"
#include "CTRAFFICLIGHT.h"


class Lane
{
private:
	vector<COBSTACLE*> obstacle;
	int num;
	vector<CTRAFFICLIGHT> lights;
	int numTrafficLight; 
	Texture texture;
	Sprite sprite;
	Vector2f position;
public:
	
	Lane(int typeObstacle ,int dir,int num, float speed, string texture_dir, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void update(float delta_time);
	//void render(RenderTarget* target);


	friend class CPEOPLE;
};

