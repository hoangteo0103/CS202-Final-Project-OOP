#pragma once
#include "Base.h"
#include "LanePack.h"
enum PLAYERSTATE { MOVE = 0, IDLE = 1, DEATH = 2 };


class CPEOPLE : public Object
{
private:
	int state;
	int row;
	int face_direction; // 0 - down, 1 - left, 2 - right, 3 - up
	bool pause;

public:
	CPEOPLE() {};
	CPEOPLE(string path, sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos);
	void move(float delta_time, const sf::Vector2u map_size, LanePack*& lane_management);
	void update(float delta_time, const sf::Vector2u map_size, LanePack*& lane_management);
	void updateAfterDead(float delta_time, const sf::Vector2u map_size);
	bool isCollision(LanePack*& lane_management);
	void reset(sf::Vector2f pos);
	void setDead() { this->state = PLAYERSTATE::DEATH; };
	bool isDead();
	bool isDeadFrameEnd();
	void changeSkin(string path);

	//Load and save 
	CPEOPLE(istream& in);
	void saveCPeople(ostream& out);
};

