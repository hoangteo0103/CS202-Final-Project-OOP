#include "LanePack.h"


using namespace std;

LanePack::LanePack(int distance) : distance_factor(distance) {
}

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
	this->win_line_y = win_line_y;

	random_device rd;
	mt19937 rng(rd());

	cout << "number of lane: " << numberLane << endl;
	for (int i = 0; i < this->numberLanes; ++i) {
		int y_position = (distance_factor+ROADHEIGHT) * i + win_line_y + offset;
		cout << y_position << endl; 
		posObstacles.push_back(y_position);
		//cout << "y_position: " << y_position << endl;
		uniform_int_distribution<int> range(0, 1);
		int type = range(rng);
		int dir = range(rng) + 1;
		Lane *new_lane = new Lane(0, dir, 3, speed, type, sf::Vector2f(0, y_position));
		lanes.push_back(new_lane);
	}
	this->generateObstacle();
}

void LanePack::generateObstacle()
{
	random_device rd;
	mt19937 rng(rd());
	for (int i = 0; i < numberLanes - 1; i++)
	{
		uniform_int_distribution<int> rangeType(0, OBSTACLETEXTUREPATH.size() - 1);
		uniform_int_distribution<int> rangeNum(10 , 20);
		int num = rangeNum(rng);
		cout << num << endl; 
		int previous = 0; 
		for (int j = 0; j < num; j++)
		{
			
			int type = rangeType(rng);
			if (2880 < previous + SIZEOBSTACLE[type]) break;
			uniform_int_distribution <int > range2(previous, min(2880 , previous + ( j + 2 ) *  SIZEOBSTACLE[type]));
			Vector2f pos = Vector2f(range2(rng), posObstacles[i] + ROADHEIGHT);
			COBSTACLE* now = new COBSTACLE(OBSTACLETEXTUREPATH[type], Vector2u(1, 1), 0, 0, pos, 0);
			obstacles.push_back(now);
			previous = pos.x + SIZEOBSTACLE[type];
			obstacleSprites.push_back(now->sprite);

		}
		
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
		 obstacle->draw(window);
}

void LanePack::reset(int speed , int level, sf::Vector2u map_size, int win_line_y)
{
	for (auto lane : lanes)
		delete lane;
	obstacles.clear();
	obstacleSprites.clear();
	posObstacles.clear();
	lanes.clear();
	this->init(speed , level, map_size, win_line_y);
}

int LanePack::getNumOfLanes() {
	return lanes.size();
}

void LanePack::saveLanePack(ostream& out)
{
	out << speed << ' ' << numberLanes << distance_factor << win_line_y;
}

void LanePack::loadLanePack(istream& in)
{
	in >> speed >> numberLanes >> distance_factor >> win_line_y; 

	int offset = 50;
	for (int i = 0; i < this->numberLanes; ++i) {
		int y_position = (distance_factor + ROADHEIGHT) * i + win_line_y + offset;
		Lane* new_lane = new Lane(in);
		lanes.push_back(new_lane);
	}
	this->generateObstacle();
}