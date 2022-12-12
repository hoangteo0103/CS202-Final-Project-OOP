#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(Vector2f pos, float red_time, float yellow_time, float green_time)
{
	now_time = 0;
	state = 0;
	texture.loadFromFile("trafficlight.png");
	this->red_time = red_time;
	this->yellow_time = yellow_time;
	this->green_time = green_time;
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

void CTRAFFICLIGHT::draw(RenderWindow& window)
{
	cout << state << endl; 
	IntRect rect; 
	rect.height = 48;
	rect.width = float(198) / 4.f; // depend on the texture 
	rect.top = 0;
	rect.left = state * rect.width; 
	sprite.setTextureRect(rect);
	sprite.setScale(2.f, 2.f); 
	window.draw(sprite);
}

void CTRAFFICLIGHT::render(RenderTarget* target)
{

}

void CTRAFFICLIGHT::transition(float delta_time)
{
	now_time += delta_time;
	cout << now_time << ' ' << red_time << ' ' << green_time << ' ' << red_time << endl;
	if (now_time <= red_time)
	{
		state = 0;
	}
	else if (now_time <= red_time+yellow_time)
	{
		state = 1;
	}
	else if (now_time <= red_time + yellow_time + green_time)
	{
		state = 2;
	}	
	if (now_time > red_time + yellow_time + green_time)
	{
		now_time = 0;
		state = 0; 
	}
}
