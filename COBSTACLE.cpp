#include "COBSTACLE.h"


COBSTACLE::COBSTACLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos, int dir) : Object(path, image_contain, switch_time, speed, pos)
{
	this->direction = dir;
}
		

void COBSTACLE::move(float delta_time)
{
	Mouvment mouvment;
	// 1 Left 2 Right 
	mouvment.goDirection(4 - direction, sprite, speed, delta_time);
	//cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << endl; 
	this->animation.update(0 , delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
	if(direction == 1)
		this->sprite.setScale(-1.f, 1.f);
}