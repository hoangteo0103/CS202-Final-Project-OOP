#pragma once
#include "Lane.h"
#include "Base.h"


class LanePack
{
private:
	vector<Lane> lanes;
	vector<sf::Vector2u> position;
public :
	void init(int level);
	void update(float delta_time); 
	void reset();
};

