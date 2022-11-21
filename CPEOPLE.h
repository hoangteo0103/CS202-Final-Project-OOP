#pragma once
#include "Base.h"
class CPEOPLE : public Object
{
private:
	float total_time, switch_time;
	sf::Vector2u image_contain;
	sf::Vector2u current_image;

	void mode();

	

public:
	sf::IntRect uv_rect;

	CPEOPLE(sf::Texture* texture, sf::Vector2u image_contain, float switch_time);

	void update(int row, float delta_time);
};

