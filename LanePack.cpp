#include "LanePack.h"


using namespace std;

LanePack::~LanePack() {
	for (auto lane : lanes)
		delete lane;
}

void LanePack::init(int level, sf::Vector2u map_size, int win_line_y)
{
	int numberLane;
	switch (level)
	{
	case 1: case 2: case 3:
		numberLane = 5;
		break;
	case 4: case 5:
		numberLane = 6;
		break;
	default:
		cout << "INVALID LEVEL" << endl;
		exit(0);
	}

	int factor = map_size.y / (numberLane + 4);
	for (int i = 0; i < numberLane; ++i) {
		int y_position = factor * i + win_line_y;
		Lane *new_lane = new Lane(0, 2, 3, 10.f, "clayroad.png", sf::Vector2f(0, y_position));
		lanes.push_back(new_lane);
	}

}

void LanePack::update(float delta_time)
{
	for (auto lane : lanes)
		lane->update(delta_time);
}

void LanePack::draw(sf::RenderWindow& window) {
	for (auto lane : lanes)
		lane->draw(window);
}

void LanePack::reset()
{

}