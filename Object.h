#pragma once
#include "Base.h"

class Animation {
private:
	float total_time, switch_time;
	sf::Vector2u image_contain;
	sf::Vector2u current_image;
	int player_state;

public:
	void update(int row, float delta_time /*int direction*/);
	sf::IntRect uv_rect;
	Animation(sf::Texture* texture, sf::Vector2u image_contain, float switch_time);
	Animation();

};


class Mouvment {
public:
	Mouvment() {};
	void goDirection(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time);
};	

class Object
{
private:
public:
	Texture texture;
	Sprite sprite;
	float speed;
	float origin_speed; 
	Animation animation;
	Object() {};
	Object(string path, Vector2u image_contain, float switch_time, float speed, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void render(RenderTarget* target);
	//void move(float delta_time);
	void updateEvent();
	//bool collide(Object& other);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
};

