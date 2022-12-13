#pragma once

#include "Base.h"

class CView
{
private:
	sf::View _view;
	sf::Vector2u window_size, map_size;
	sf::Vector2f position;
public:
	CView() {};
	CView(sf::RenderWindow& window, const sf::Vector2u& map_size);
	void init(sf::RenderWindow& window, const sf::Vector2u& map_size);
	void update(sf::RenderWindow& window, Object& player);
	sf::Vector2f getCenter();
};

