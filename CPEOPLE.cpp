#include "CPEOPLE.h"


CPEOPLE::CPEOPLE(string path,  sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos) : Object(path , image_contain , switch_time , speed , pos) {
	row = 0;
	face_direction = 0;
}

void CPEOPLE::move(float delta_time) {
	Mouvment mouvment;
	int temp_size = 740;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (this->getPosition().x < temp_size) {
			mouvment.goDirection(2, sprite, speed, delta_time);
			row = 2;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (this->getPosition().x > 0) {
			mouvment.goDirection(3, sprite, speed, delta_time);
			row = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (this->getPosition().y > 0) {
			mouvment.goDirection(0, sprite, speed, delta_time);
			row = 3;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (this->getPosition().y < temp_size) {
			mouvment.goDirection(1, sprite, speed, delta_time);
			row = 0;
		}
	}
	//cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << endl; 
	this->animation.update(row, delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
}