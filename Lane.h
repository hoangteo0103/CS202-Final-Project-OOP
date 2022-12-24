#pragma once
#include "COBSTACLE.h"
#include "CTRAFFICLIGHT.h"
#include <random>

const vector<string> ROADTEXTUREPATH = { "asset\\road\\road0.png", "asset\\road\\road1.png" , "asset\\road\\road2.png" , "asset\\road\\road3.png" };

class Lane
{
private:
	vector<COBSTACLE*> obstacle;
	int num;
	vector<CTRAFFICLIGHT*> lights;
	int numTrafficLight; 
	Texture texture;
	int type; 
	int dir;
	Sprite sprite;
	Vector2f position;
public:
	// type = 0 -> road for animal, type = 1 -> road for car
	Lane(int typeObstacle ,int dir,int num, float speed, int type, Vector2f pos);
	~Lane();
	void draw(sf::RenderWindow& window);
	void update(float delta_time);
	void updateSpeed();
	void checkEnd();
	//void render(RenderTarget* target);

	friend class CPEOPLE;
};

