#include "CView.h"

CView::CView(RenderWindow& window, const Vector2u& map_size) {
	this->window_size.x = window.getSize().x;
	this->window_size.y = window.getSize().y;
	this->map_size = map_size;
	this->position.x = this->window_size.x / 2;
	this->position.y = this->window_size.y / 2;
	_view.reset(FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(Vector2f(map_size.x/2, map_size.y - 50));
	window.setView(_view);
}

void CView::init(RenderWindow& window, const Vector2u& map_size) {
	this->window_size.x = window.getSize().x;
	this->window_size.y = window.getSize().y;
	this->map_size = map_size;
	this->position.x = this->window_size.x / 2;
	this->position.y = this->window_size.y / 2;
	_view.reset(FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(Vector2f(map_size.x / 2, map_size.y - 50));
	window.setView(_view);
}

void CView::update(RenderWindow& window, Object& player) {
	if (player.getPosition().x > window_size.x / 2 && player.getPosition().x < map_size.x - window_size.x/2)
		position.x = player.getPosition().x;
	if (player.getPosition().y > window_size.y / 2 && player.getPosition().y < map_size.y - window_size.y / 2)
		position.y = player.getPosition().y;
	_view.setCenter(position);
	window.setView(_view);
	//cout << "position.x " << position.x << " position.y" << position.y << endl;
}

Vector2f CView::getCenter()
{
	return _view.getCenter();
}

void CView::reset(RenderWindow& window, Object& player) {
	_view.setCenter(player.getPosition());
	window.setView(_view);
}


void CView::loadGame(istream& in, RenderWindow& window, const Vector2u& map_size) {
	in >> this->position.x >> this->position.y;
	//cout << "position x: " << position.x << endl;
	//cout << "position y: " << position.y << endl;
	this->window_size.x = window.getSize().x;
	this->window_size.y = window.getSize().y;
	this->map_size = map_size;
	_view.reset(FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(position);
	window.setView(_view);
}

void CView::saveGame(ostream& out) {
	out << this->position.x << " " << this->position.y << endl;
}