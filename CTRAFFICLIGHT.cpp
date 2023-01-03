#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(Vector2f pos, float red_time, float yellow_time, float green_time)
{
	now_time = 0;
	state = 0;
	texture.loadFromFile("asset/trafficlight/trafficlight.png");
	this->red_time = red_time;
	this->yellow_time = yellow_time;	
	this->green_time = green_time;
	sprite.setTexture(texture);
	sprite.setPosition(pos);
}
 
void CTRAFFICLIGHT::draw(RenderWindow& window)
{
	IntRect rect; 
	rect.height = texture.getSize().y;
	rect.width = texture.getSize().x / 4.f; // depend on the texture 
	rect.top = 0;
	rect.left = (state + 1 ) * rect.width; 
	sprite.setTextureRect(rect);
	sprite.setScale(2.f, 2.f); 
	window.draw(sprite);
}

void CTRAFFICLIGHT::render(RenderTarget* target)
{

}

bool CTRAFFICLIGHT::isVehiclePass()
{
	return state != 2;
}

float CTRAFFICLIGHT::getPos()
{
	return this->sprite.getPosition().x;
}

void CTRAFFICLIGHT::transition(float delta_time)
{
	now_time += delta_time;
	if (now_time <= green_time)
	{
		state = 0;
	}
	else if (now_time <= green_time +yellow_time)
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

CTRAFFICLIGHT::CTRAFFICLIGHT(istream& in)
{
	texture.loadFromFile("asset/trafficlight/trafficlight.png");
	in >> state >> now_time; 
	in >> red_time >> yellow_time >> green_time; 
	float x, y;
	in >> x >> y;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(x,y));
}

void CTRAFFICLIGHT::saveLight(ostream& out)
{
	out << state << ' ' << now_time << '\n';
	out << red_time << ' ' << yellow_time << ' ' << green_time << '\n';
	out << this->sprite.getPosition().x << ' ' << this->sprite.getPosition().y << '\n';
}
