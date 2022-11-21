#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(sf::Texture* texture, sf::Vector2u image_contain, float switch_time) {
	this->image_contain = image_contain;
	this->switch_time = switch_time;
	total_time = 0.f;
	current_image.x = 0;

	uv_rect.width = texture->getSize().x / float(image_contain.x);
	uv_rect.height = texture->getSize().y / float(image_contain.y);
}

void CPEOPLE::update(int row, float delta_time) {
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