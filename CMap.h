#pragma once
#include "Base.h"
using namespace sf;
using namespace std;

class CMap
{
private:
	Vector2u size;
	Texture texture;
	Sprite sprite;
	

public:
	CMap() {};
	CMap(string dir);
	void init(string dir); 

	void draw(RenderWindow& window);
	Vector2u getSize() const;
};


