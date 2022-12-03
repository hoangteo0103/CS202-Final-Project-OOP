#pragma once

#include "Base.h"

class CMap
{
private:
	sf::Vector2u size;
	sf::Texture texture;
	sf::Sprite sprite;
	

public:
	CMap(const std::string& dir);

	void draw(sf::RenderWindow& window);
	sf::Vector2u getSize() const;
};


