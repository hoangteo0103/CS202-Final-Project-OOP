#include "CView.h"
#include <iostream>
using namespace std;
CView::CView(sf::RenderWindow& window, const sf::Vector2u& map_size) {
	this->window_size.x = window.getSize().x;
	this->window_size.y = window.getSize().y;
	this->map_size = map_size;
	this->position.x = this->window_size.x / 2;
	this->position.y = this->window_size.y / 2;
	_view.reset(sf::FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(sf::Vector2f(map_size.x/2, map_size.y - 50));
	window.setView(_view);
}

void CView::init(sf::RenderWindow& window, const sf::Vector2u& map_size) {
	this->window_size.x = window.getSize().x;
	this->window_size.y = window.getSize().y;
	this->map_size = map_size;
	this->position.x = this->window_size.x / 2;
	this->position.y = this->window_size.y / 2;
	_view.reset(sf::FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(sf::Vector2f(map_size.x / 2, map_size.y - 50));
	window.setView(_view);
}

void CView::update(sf::RenderWindow& window, Object& player) {
	if (player.getPosition().x > window_size.x / 2 && player.getPosition().x < map_size.x - window_size.x/2)
		position.x = player.getPosition().x;
	if (player.getPosition().y > window_size.y / 2 && player.getPosition().y < map_size.y - window_size.y / 2)
		position.y = player.getPosition().y;
	_view.setCenter(position);
	window.setView(_view);
	//cout << "position.x " << position.x << " position.y" << position.y << endl;
}

sf::Vector2f CView::getCenter()
{
	return _view.getCenter();
}

void CView::reset(sf::RenderWindow& window, Object& player) {
	_view.setCenter(player.getPosition());
	window.setView(_view);
}


void CView::loadGame(istream& in, sf::RenderWindow& window, const sf::Vector2u& map_size) {
	in >> this->position.x >> this->position.y;
	this->map_size = map_size;
	_view.reset(sf::FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	_view.setCenter(position);
	window.setView(_view);
}

void CView::saveGame(ostream& out) {
	out << this->position.x << " " << this->position.y << endl;
}