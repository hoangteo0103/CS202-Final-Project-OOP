#pragma once
#include "Base.h"
#include <iostream>

using namespace sf;
using namespace std;

class CView
{
private:
	View _view;
	Vector2u window_size, map_size;
	Vector2f position;

public:
	CView() {};
	CView(RenderWindow& window, const Vector2u& map_size);
	void init(RenderWindow& window, const Vector2u& map_size);
	void update(RenderWindow& window, Object& player);
	Vector2f getCenter();
	void reset(RenderWindow& window, Object& player);

	void loadGame(istream& in, RenderWindow& window, const Vector2u& map_size);
	void saveGame(ostream& out);
};

