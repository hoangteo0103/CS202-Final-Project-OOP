#pragma once
#include "Base.h"

class Animation {
private:
	float total_time, switch_time;
	sf::Vector2u image_contain;
	sf::Vector2u current_image;

public:
	void update(int row, float delta_time /*int direction*/);
	void updatePlayer(int row, float delta_time /*int direction*/);
	void updatePlayerAfterDead(int row, float delta_time);
	bool isFrameEnd(int state);
	void resetFrameDead();
	sf::IntRect uv_rect;
	Animation(sf::Texture* texture, sf::Vector2u image_contain, float switch_time);
	Animation();

	// Load and save animation
	void saveAnimation(ostream& out);
	void loadAnimation(istream& in); 
};


class Mouvment {
public:
	Mouvment() {};
	void goDirection(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time);
	void goDirectionPlayer(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time, vector<Sprite> obstacles);
};	

class Object
{
private:
public:
	Texture texture;
	Sprite sprite;
	float speed;
	string path; 
	float origin_speed; 
	Animation animation;
	Object() {};
	Object(string path, Vector2u image_contain, float switch_time, float speed, Vector2f pos);
	void draw(sf::RenderWindow& window);
	void render(RenderTarget* target);
	//void move(float delta_time);
	void updateEvent();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getSize();
	
	//Load and save 
	Object(istream& in);
	void saveObject(ostream& out);
};

