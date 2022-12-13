#pragma once
#include "COBSTACLE.h"
#include "CTRAFFICLIGHT.h"
const vector<sf::Vector2u> block = { sf::Vector2u(100,700),sf::Vector2u(300,700), sf::Vector2u(500,700), sf::Vector2u(700,700), sf::Vector2u(900,700), sf::Vector2u(1100,700) };

class Lane
{
private :
	vector<COBSTACLE*> obstacle;
	vector<CTRAFFICLIGHT> lights;
	int numTrafficLight; 
	Texture texture;
	Sprite sprite;
	int num;
public :
	
	void init();
	Lane(int typeObstacle ,int dir,int num, float speed, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void update(float delta_time);
	void render(RenderTarget* target);


	friend class CPEOPLE;
};

