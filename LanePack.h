#pragma once
#include "Lane.h"
#include "Base.h"
class LanePack
{
private:
	vector<Lane> lanes; 
public :
	void init();
	void update(float delta_time); 
	void reset();
};

