#pragma once
#include "Lane.h"
#include "Base.h"
#include <random>
const vector<sf::Vector2f> block = { sf::Vector2f(100,700),sf::Vector2f(300,700), sf::Vector2f(500,700), sf::Vector2f(700,700), sf::Vector2f(900,700), sf::Vector2f(1100,700) };

class LanePack
{
private:
	vector<Lane*> lanes;
	vector<sf::Vector2f> position;
public:

	~LanePack();
	void init(int level, sf::Vector2u map_size, int win_line_y);
	void update(float delta_time);
	void draw(sf::RenderWindow& window);
	void reset(int level, sf::Vector2u map_size, int win_line_y);

	friend class CPEOPLE;
};

