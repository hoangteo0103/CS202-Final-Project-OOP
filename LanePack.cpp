#include "LanePack.h"


using namespace std;

LanePack::LanePack(int distance) : distance_factor(distance) {}

LanePack::~LanePack() {
	for (auto lane : lanes)
		delete lane;
}

void LanePack::init(int level, sf::Vector2u map_size, int win_line_y)
{
	int numberLane;
	switch (level)
	{
	case 1: case 2:
		numberLane = 6;
		break;
	case 3: case 4:
		numberLane = 7;
		break;
	case 5:
		numberLane = 8;
		break;
	default:
		return;
	}

	int offset = 50;

	random_device rd;
	mt19937 rng(rd());

	cout << "number of lane: " << numberLane << endl;

	for (int i = 0; i < numberLane; ++i) {
		cout << "i: " << i << endl;
		int y_position = (distance_factor+ROADHEIGHT) * i + win_line_y + offset;
		//cout << "y_position: " << y_position << endl;
		uniform_int_distribution<int> range(0, 1);
		int type = range(rng);
		Lane *new_lane = new Lane(0, 2, 3, 200.f, type, sf::Vector2f(0, y_position));
		lanes.push_back(new_lane);
	}

	cout << "size: " << lanes.size() << endl;
}

void LanePack::update(float delta_time)
{
	for (auto lane : lanes)
	{
		lane->updateSpeed();
		lane->update(delta_time);
		
	}
}

void LanePack::draw(sf::RenderWindow& window) {
	for (auto lane : lanes)
		lane->draw(window);
}

void LanePack::reset(int level, sf::Vector2u map_size, int win_line_y)
{
	for (auto lane : lanes)
		delete lane;

	lanes.clear();
	this->init(level, map_size, win_line_y);
}

int LanePack::getNumOfLanes() {
	return lanes.size();
}