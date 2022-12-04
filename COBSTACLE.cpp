#include "COBSTACLE.h"


COBSTACLE::COBSTACLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos, int dir) : Object(path, image_contain, switch_time, speed, pos)
{
	this->direction = dir;
}
		

void COBSTACLE::move(float delta_time, const sf::Vector2u map_size)
{
	Mouvment mouvment;
	// 1 Left 2 Right 
	mouvment.goDirection(direction, sprite, speed, delta_time);
	//cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << endl; 
	this->animation.update(0 , delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
	if (sprite.getPosition().x > map_size.x)
	{
		sprite.setPosition(sf::Vector2f(0.0f-animation.uv_rect.width, sprite.getPosition().y));
	}
	else if (sprite.getPosition().x < 0.0f - animation.uv_rect.width)
	{
		sprite.setPosition(sf::Vector2f(map_size.x, sprite.getPosition().y));
	}
}

CVehicle::CVehicle(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos, int dir) :COBSTACLE(path, image_contain, switch_time, speed, pos, dir)
{
}

CAnimal::CAnimal(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos, int dir) : COBSTACLE(path, image_contain, switch_time, speed, pos, dir)
{
}

void CAnimal::tell()
{
}
