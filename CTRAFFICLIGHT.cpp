#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(Vector2f pos, float red_time, float yellow_time, float green_time)
{
	state = 1;
	texture.loadFromFile("trafficlight.png");
	this->red_time = red_time;
	this->yellow_time = yellow_time;
	this->green_time = green_time;
}

void CTRAFFICLIGHT::draw(RenderWindow& window)
{
	IntRect rect; 
	rect.height = texture.getSize().y;
	rect.width = 100; // depend on the texture 
	rect.top = 0;
	rect.left = (state - 1) * rect.width; 
	sprite.setTextureRect(rect);
	window.draw(sprite);
}

void CTRAFFICLIGHT::render(RenderTarget* target)
{

}

void CTRAFFICLIGHT::transition(float delta_time)
{
	now_time += delta_time;
	now_time = now_time > (yellow_time + green_time + red_time) ? 0 : now_time;
	if (now_time <= red_time)
	{
		state = 1;
	}
	else if (now_time <= yellow_time)
	{
		state = 2;
	}
	else {
		state = 3;
	}	
}
