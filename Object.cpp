#include "Object.h"

Animation::Animation() {}

Animation::Animation(sf::Texture* texture, sf::Vector2u image_contain, float switch_time) {
	this->image_contain = image_contain;
	this->switch_time = switch_time;
	total_time = 0.f;
	current_image.x = 0;

	uv_rect.width = texture->getSize().x / float(image_contain.x);
	uv_rect.height = texture->getSize().y / float(image_contain.y);
}

void Animation::update(int row, float delta_time /*int direction*/) {
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


void Mouvment::goDirection(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time)
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

Object::Object(string path, Vector2u image_contain, float switch_time, float speed , Vector2f pos)
{
	if (!(texture.loadFromFile(path)))
	{
		cout << "Could Not Load File.." << endl;
	}
	this->speed = speed; 
	sprite.setTexture(texture);
	this->sprite.setPosition(pos);
	this->animation = Animation(&texture, image_contain, switch_time); 
}

void Object::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}