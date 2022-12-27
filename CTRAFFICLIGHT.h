#pragma once
#include "Base.h"
class CTRAFFICLIGHT
{
private :
	int state;
	float now_time; 
	float red_time, yellow_time, green_time; 
	Sprite sprite;
	Texture texture;
public :
	CTRAFFICLIGHT(Vector2f pos , float red_time , float yellow_time , float green_time);
	void draw(RenderWindow& window);
	void render(RenderTarget* target);
	void transition(float delta_time);
	bool isVehiclePass()
	{
		return state != 2;
	}
	float getPos();

	// Load and save 
	CTRAFFICLIGHT(istream& in);
	void saveLight(ostream& out);
};
	
