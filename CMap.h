#pragma once

#include "Base.h"

class CMap
{
private:
	sf::Vector2u size;
	sf::Texture texture;
	sf::Sprite sprite;
	

public:
	CMap() {};
	CMap(std::string dir);
	void init(string dir); 

	void draw(sf::RenderWindow& window);
	sf::Vector2u getSize() const;
};


