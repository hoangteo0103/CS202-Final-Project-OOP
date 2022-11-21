#include "CPEOPLE.h"

CPEOPLE::Animation::Animation() {}

CPEOPLE::Animation::Animation(sf::Texture* texture, sf::Vector2u image_contain, float switch_time) {
	this->image_contain = image_contain;
	this->switch_time = switch_time;
	total_time = 0.f;
	current_image.x = 0;

	uv_rect.width = texture->getSize().x / float(image_contain.x);
	uv_rect.height = texture->getSize().y / float(image_contain.y);
}

void CPEOPLE::Animation::update(int row, float delta_time /*int direction*/) {
	current_image.y = row;
	total_time += delta_time;
	if (total_time >= switch_time) {
		total_time -= switch_time;
		++current_image.x;

		if (current_image.x >= image_contain.x) {
			current_image.x = 0;
		}
	}

	uv_rect.left = current_image.x * uv_rect.width;
	uv_rect.top = current_image.y * uv_rect.height;
}


void CPEOPLE::Mouvment::goDirection(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time)
{
	float dis = speed * delta_time;
	switch (dir) {
	case 0:
		spritesheet.move(sf::Vector2f(0, -dis));
		break;
	case 1:
		spritesheet.move(sf::Vector2f(0, dis));
		break;
	case 2:
		spritesheet.move(sf::Vector2f(dis, 0));
		break;
	case 3:
		spritesheet.move(sf::Vector2f(-dis, 0));
		break;
	}
}


CPEOPLE::CPEOPLE(sf::Texture* texture, sf::Vector2u image_contain, float switch_time, float speed) {
	this->animation = Animation(texture, image_contain, switch_time);
	this->speed = speed;
	row = 0;
	face_direction = 0;

	body.setTexture(*texture);
}


void CPEOPLE::draw(sf::RenderWindow& window) {
	window.draw(body);
}

void CPEOPLE::move(float delta_time) {
	Mouvment mouvment;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mouvment.goDirection(2, body, speed, delta_time);
		row = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mouvment.goDirection(3, body, speed, delta_time);
		row = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mouvment.goDirection(0, body, speed, delta_time);
		row = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mouvment.goDirection(1, body, speed, delta_time);
		row = 0;
	}

	this->animation.update(row, delta_time);
	this->body.setTextureRect(this->animation.uv_rect);
}