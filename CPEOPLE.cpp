#include "CPEOPLE.h"


CPEOPLE::CPEOPLE(string path,  sf::Vector2u image_contain, float switch_time, float speed, Vector2f pos) : Object(path , image_contain , switch_time , speed , pos) {
	row = 0;
	face_direction = 0;
	state = PLAYERSTATE::IDLE;
	pause = false;
}

void CPEOPLE::move(float delta_time, const sf::Vector2u map_size) {
	Mouvment mouvment;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (this->getPosition().x < map_size.x) {
			mouvment.goDirection(2, sprite, speed, delta_time);
			face_direction = 0;
			state = row = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (this->getPosition().x > 0) {
			mouvment.goDirection(3, sprite, speed, delta_time);
			face_direction = 1;
			state = row = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (this->getPosition().y > 0) {
			mouvment.goDirection(0, sprite, speed, delta_time);
			state = row = 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (this->getPosition().y < map_size.y) {
			mouvment.goDirection(1, sprite, speed, delta_time);
			state = row = 1;
		}
	}
	else {
		row = 0;
		state = 0;
	}
	/*cout << "row: " << row << endl;
	cout << sprite.getPosition().x << ' ' << sprite.getPosition().y << endl;*/
	this->animation.updatePlayer(row, delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
	this->sprite.setOrigin(this->animation.uv_rect.width / 2, this->animation.uv_rect.height / 2);
	this->sprite.setScale((face_direction == 1) ? -1.f : 1.f, 1.f);
}


void CPEOPLE::update(float delta_time, const sf::Vector2u map_size) {
	switch (state) {
	case 0 : case 1:
		move(delta_time, map_size);
		break;

	case 2:
		row = 2;
		this->animation.updatePlayer(row, delta_time);
		this->sprite.setTextureRect(this->animation.uv_rect);
		break;
	}
}


void CPEOPLE::updateAfterDead(float delta_time, const sf::Vector2u map_size) {
	row = 2;
	this->animation.updatePlayerAfterDead(row, delta_time);
	this->sprite.setTextureRect(this->animation.uv_rect);
}


bool CPEOPLE::isCollision(LanePack*& lane_management) {
	for (auto lane : lane_management->lanes)
		for (auto obstacle : lane->obstacle)
			if (Collision::PixelPerfectTest(this->sprite, obstacle->sprite)) {
				state = PLAYERSTATE::DEATH;
				return true;
			}
	return false;
}

bool CPEOPLE::isDead()
{
	return this->state == PLAYERSTATE::DEATH;
}

bool CPEOPLE::isDeadFrameEnd()
{
	return this->animation.isFrameEnd(2);
}

void CPEOPLE::reset(sf::Vector2f pos) {
	this->setPosition(pos);
	this->state = PLAYERSTATE::IDLE;
}
