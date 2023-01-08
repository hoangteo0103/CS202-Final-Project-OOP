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

		uniform_int_distribution<int> numObs(5, 10);
		Lane *new_lane = new Lane(0, dir, numObs(rng), speed, type, sf::Vector2f(0, y_position));
		lanes.push_back(new_lane);
	}
	this->generateObstacle();
}

void LanePack::generateObstacle()
{
	random_device rd;
	mt19937 rng(rd());
	listPosObstacle.resize(numberLanes-1);
	for (int i = 0; i < numberLanes - 1; i++)
	{
		uniform_int_distribution<int> rangeType(0, OBSTACLETEXTUREPATH.size() - 1);
		uniform_int_distribution<int> rangeNum(10 , 20);
		int num = rangeNum(rng);
		int previous = 0;
		int realNum = 0;
		for (int j = 0; j < num; j++)
		{
			
			int type = rangeType(rng);
			if (2880 < previous + SIZEOBSTACLE[type]) break;
			uniform_int_distribution <int > range2(previous, min(2880 , previous + ( j + 2 ) *  SIZEOBSTACLE[type]));
			int posX = range2(rng);
			Vector2f pos = Vector2f(posX, posObstacles[i] + ROADHEIGHT);
			COBSTACLE* now = new COBSTACLE(OBSTACLETEXTUREPATH[type], Vector2u(1, 1), 0, 0, pos, 0);
			listPosObstacle[i].push_back({ posX , type });
			obstacles.push_back(now);
			previous = pos.x + SIZEOBSTACLE[type];
			obstacleSprites.push_back(now->sprite);
			realNum++;
		}
		listNumObstacle.push_back(realNum);
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

	for (auto obstacle : obstacles)
		 obstacle->draw(window);

	for (auto lane : lanes)
		lane->draw(window);
}

void LanePack::reset(int speed , int level, sf::Vector2u map_size, int win_line_y)
{
	for (auto lane : lanes)
		delete lane;
	obstacles.clear();
	obstacleSprites.clear();
	posObstacles.clear();
	lanes.clear();
	listNumObstacle.clear();
	listPosObstacle.clear();
	this->init(speed , level, map_size, win_line_y);
}

int LanePack::getNumOfLanes() {
	return lanes.size();
}

void LanePack::saveLanePack(ostream& out)
{
	out << speed << ' ' << numberLanes << ' ' << distance_factor << ' ' <<  win_line_y << '\n';\
	
	for (int i = 0; i < numberLanes; i++)
	{
		lanes[i]->saveLane(out);
	}
	for (int i = 0; i < numberLanes - 1; i++)
	{
		out << listNumObstacle[i] << '\n';
		for (int j = 0; j < listNumObstacle[i]; j++)
			out << listPosObstacle[i][j].first << ' ' << listPosObstacle[i][j].second << '\n';
	}
}
void LanePack::loadLanePack(istream& in)
{
	in >> speed >> numberLanes >> distance_factor >> win_line_y; 
	listNumObstacle.resize(numberLanes-1);
	listPosObstacle.resize(numberLanes-1);
	
	
	int offset = 50;
	for (int i = 0; i < this->numberLanes; ++i) {
		int y_position = (distance_factor + ROADHEIGHT) * i + win_line_y + offset;
		Lane* new_lane = new Lane(in);
		lanes.push_back(new_lane);
		posObstacles.push_back(y_position);
	}

	for (int i = 0; i < numberLanes - 1; i++)
	{
		in >> listNumObstacle[i];
		listPosObstacle[i].resize(listNumObstacle[i]);
		for (int j = 0; j < listNumObstacle[i]; j++)
		{
			in >> listPosObstacle[i][j].first >> listPosObstacle[i][j].second;
			int type = listPosObstacle[i][j].second;
			int posX = listPosObstacle[i][j].first;
			Vector2f pos = Vector2f(posX, posObstacles[i] + ROADHEIGHT);
			COBSTACLE* now = new COBSTACLE(OBSTACLETEXTUREPATH[type], Vector2u(1, 1), 0, 0, pos, 0);
			obstacles.push_back(now);
			obstacleSprites.push_back(now->sprite);
		}
	}
}