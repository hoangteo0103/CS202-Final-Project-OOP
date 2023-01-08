#pragma once
#include "COBSTACLE.h"
#include "CTRAFFICLIGHT.h"
#include <random>
#include <map>

const vector<string> ROAD_ANIMAL_TEXTURE_PATH = { "asset\\road\\road0.png", "asset\\road\\road1.png" };
const vector<string> ROAD_VEHICLE_TEXTURE_PATH = { "asset\\road\\road2.png" , "asset\\road\\road3.png" };


const vector<pair<string, sf::Vector2u>> VEHICLE_TEXTURE_PATH = { {"asset\\vehicle\\ambu.png", sf::Vector2u(1,1)}, {"asset\\vehicle\\bus.png", sf::Vector2u(1,1)}, {"asset\\vehicle\\tank.png", sf::Vector2u(1,1)}, {"asset\\vehicle\\truck.png", sf::Vector2u(1,1)}, {"asset\\vehicle\\mer.png", sf::Vector2u(2,1)}, {"asset\\vehicle\\van.png", sf::Vector2u(2,1)} };
const vector<pair<string, sf::Vector2u>> ANIMAL_TEXTURE_PATH = { {"asset\\animal\\snake.png", sf::Vector2u(3,1)}, {"asset\\animal\\bird.png", sf::Vector2u(4,1)}, /*{"asset\\animal\\anaconda.png", sf::Vector2u(4,1)},*/ /*{"asset\\animal\\antelope.png", sf::Vector2u(4,1)},*/ {"asset\\animal\\wolf.png", sf::Vector2u(5,1)}, {"asset\\animal\\bear.png", sf::Vector2u(4,1)}, /*{"asset\\animal\\rat.png", sf::Vector2u(4,1)},*/ {"asset\\animal\\slime.png", sf::Vector2u(10,1)}, };
class Lane
{
private:
	vector<COBSTACLE*> obstacle;
	int num;
	vector<CTRAFFICLIGHT*> lights;
	int numTrafficLight; 
	int type; 
	int dir;
	float now_time;
	float switch_time; 
	Texture texture;
	Sprite sprite;
	Vector2f position;
	string obstacle_path, road_path;

public:
	// type = 0 -> road for animal, type = 1 -> road for car
	Lane(int typeObstacle ,int dir,int num, float speed, int type, Vector2f pos);
	~Lane();
	void draw(sf::RenderWindow& window);
	void update(float delta_time);
	void updateSpeed();
	void checkEnd();
	//void render(RenderTarget* target);
	friend class CPEOPLE;
	// Load and save 
	Lane(istream& in);
	void saveLane(ostream& out);

};

