#include "LanePack.h"


using namespace std;

LanePack::LanePack(int distance) : distance_factor(distance) {}

LanePack::~LanePack() {
	for (auto lane : lanes)
		delete lane;
}

void LanePack::init(int speed , int level, sf::Vector2u map_size, int win_line_y)
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
	this->speed = speed;
	int offset = 50;
	this->numberLanes = numberLane;

	random_device rd;
	mt19937 rng(rd());

	cout << "number of lane: " << numberLane << endl;

	for (int i = 0; i < numberLane; ++i) {
		cout << "i: " << i << endl;
		int y_position = (distance_factor+ROADHEIGHT) * i + win_line_y + offset;
		posObstacles.push_back(y_position + ROADHEIGHT);
		//cout << "y_position: " << y_position << endl;
		uniform_int_distribution<int> range(0, 1);
		int type = range(rng);
		Lane *new_lane = new Lane(0, 2, 3, speed, type, sf::Vector2f(0, y_position));
		lanes.push_back(new_lane);
	}
	this->generateObstacle();
}

void LanePack::generateObstacle()
{
	random_device rd;
	mt19937 rng(rd());
	for (int i = 0; i < numberLanes; i++)
	{
		uniform_int_distribution<int> range(0, OBSTACLETEXTUREPATH.size() - 1);
		int type = range(rng); 
		uniform_int_distribution <int > range2(0, 2880 - SIZEOBSTACLE[type]);
		Vector2f pos = Vector2f(posObstacles[i] + ROADHEIGHT , range2(rng));
		COBSTACLE* now = new COBSTACLE(OBSTACLETEXTUREPATH[type], Vector2u(1, 1), 0, 0, pos, 0); 
		obstacles.push_back(now);
	}
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
	for (auto obstacle : obstacles)
		cout << 1 , obstacle->draw(window);
}

void LanePack::reset(int speed , int level, sf::Vector2u map_size, int win_line_y)
{
	for (auto lane : lanes)
		delete lane;
	obstacles.clear();
	posObstacles.clear();
	lanes.clear();
	this->init(speed , level, map_size, win_line_y);
}

int LanePack::getNumOfLanes() {
	return lanes.size();
}