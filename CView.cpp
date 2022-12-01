#include "CView.h"

CView::CView(const sf::Vector2f& window_size) {
	this->window_size = window_size;
	_view.reset(sf::FloatRect(0, 0, this->window_size.x, this->window_size.y));
	_view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	this->position.x = this->window_size.x / 2;
	this->position.y = this->window_size.y / 2;
}

void CView::update(sf::RenderWindow& window, Object& player) {
	int temp_size = 740;
	if (player.getPosition().x > window_size.x / 2 && player.getPosition().x < temp_size - window_size.x/2)
		position.x = player.getPosition().x;
	if (player.getPosition().y > window_size.y / 2 && player.getPosition().y < temp_size - window_size.y / 2)
		position.y = player.getPosition().y;
	_view.setCenter(position);
	window.setView(_view);
}