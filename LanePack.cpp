#include "LanePack.h"


using namespace std;

void LanePack::init(int level)
{
	int numberLane;
	switch (level)
	{
	case 1:
		numberLane = 5;
		break;
	case 2:
		numberLane = 6;
		break;
	case 3:
		numberLane = 7;
		break;
	case 4:
		numberLane = 8;
		break;
	case 5:
		numberLane = 9;
		break;
	default:
		cout << "INVALID LEVEL" << endl;
		break;
	}



}

void LanePack::update(float delta_time)
{

}

void LanePack::reset()
{

}