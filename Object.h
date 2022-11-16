#pragma once
#include "Base.h"
class Object
{
private:
	Texture texture;
	Sprite sprite;
public:
	void loadSprite(string path);
	void render(RenderTarget* target);
	void loadFrame();
	void updateEvent();
	bool collide(Object& other);
};

