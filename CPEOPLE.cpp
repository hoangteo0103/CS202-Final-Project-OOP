#include "CPEOPLE.h"


CPEOPLE::CPEOPLE(string path,  sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos) : Object(path , image_contain , switch_time , speed , pos) {
	row = 0;
	face_direction = 0;
	
}

void CPEOPLE::move(float delta_time, const sf::Vector2u map_size) {
	Mouvment mouvment;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (this->getPosition().x < map_size.x) {
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
		if (this->getPosition().y < map_size.y) {
			mouvment.goDirection(1, sprite, speed, delta_time);
			row = 0;
		}
	}
	else {
		if (row < 4) {
			row += 4;
		}
	}
	//cout << "row: " << row << endl;
	//cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << endl; 
	this->animation.update(row, delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
	
}


bool CPEOPLE::isCollision(const Lane &lane) {
	for (auto obstacle : lane.obstacle)
		if (this->sprite.getGlobalBounds().intersects(obstacle->sprite.getGlobalBounds())) {
			//this->animation.update(8, 0);
			return true;
		}
	return false;

}