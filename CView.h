#pragma once

#include "Base.h"

class CView
{
private:
	sf::View _view;
	sf::Vector2f window_size;
	sf::Vector2f position;
public:
	CView(const sf::Vector2f& window_size);
	void update(sf::RenderWindow& window, Object& player);
	
};

