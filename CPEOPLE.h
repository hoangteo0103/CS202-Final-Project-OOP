#pragma once
#include "Base.h"


class CPEOPLE : public Object
{
public:
	
	class Animation {
	private:
		float total_time, switch_time;
		sf::Vector2u image_contain;
		sf::Vector2u current_image;

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


	CPEOPLE(sf::Texture* texture, sf::Vector2u image_contain, float switch_time, float speed);

	//void mode();
	void move(float delta_time);
	//void update(float delta_time);
	void draw(sf::RenderWindow& window);

private:
	
	sf::Sprite body;
	Animation animation;
	int row;
	float speed;
	int face_direction; // 0 - down, 1 - left, 2 - right, 3 - up
};

