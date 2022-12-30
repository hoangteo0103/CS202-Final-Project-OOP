#include "Object.h"

vector<int> stateFrames = { 4 , 9 , 4 };

Animation::Animation() {}

Animation::Animation(sf::Texture* texture, sf::Vector2u image_contain, float switch_time) {
	this->image_contain = image_contain;
	this->switch_time = switch_time;
	total_time = 0.f;
	current_image.x = 0;

	uv_rect.width = texture->getSize().x / float(image_contain.x);
	uv_rect.height = texture->getSize().y / float(image_contain.y);

}

void Animation::update(int row, float delta_time) {
	current_image.y = row;
	total_time += delta_time;

	int frames = ((row < 4) ? image_contain.x : image_contain.x - 2);

	if (total_time >= switch_time) {
		
		total_time -= switch_time;
		++current_image.x;
		
		if (current_image.x >= frames) {
			current_image.x = 0;
		}
	}

	uv_rect.left = current_image.x * uv_rect.width;
	uv_rect.top = current_image.y * uv_rect.height;
}

void Animation::updatePlayer(int row, float delta_time) {
	current_image.y = row;
	total_time += delta_time;

	int frames = stateFrames[row];

	if (total_time >= switch_time) {

		total_time -= switch_time;
		++current_image.x;

		if (current_image.x >= frames) {
			current_image.x = 0;
		}
	}

	uv_rect.left = current_image.x * uv_rect.width;
	uv_rect.top = current_image.y * uv_rect.height;
}

void Animation::updatePlayerAfterDead(int row, float delta_time) {
	current_image.y = row;
	total_time += delta_time;

	int frames = stateFrames[row];

	if (total_time >= switch_time) {

		total_time -= switch_time;
		++current_image.x;

		if (current_image.x >= frames) {
			return; 
		}
	}

	uv_rect.left = current_image.x * uv_rect.width;
	uv_rect.top = current_image.y * uv_rect.height;
}

void Animation::resetFrameDead()
{
	current_image.x = 0; 
}

bool Animation::isFrameEnd(int state)
{
	int frames = stateFrames[state];
	if (current_image.x >= frames)
		return true;
	return false; 
}

void Mouvment::goDirection(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time)
{
	float dis = speed * delta_time;
	switch (dir) {
	case 1:
		spritesheet.move(sf::Vector2f(-dis, 0));
		break;
	case 2:
		spritesheet.move(sf::Vector2f(dis, 0));
		break;
	default:
		cout << "UNDEFINED OBSTACLE MOVE." << endl;
	}
}
void Mouvment::goDirectionPlayer(const int& dir, sf::Sprite& spritesheet, float speed, float delta_time, vector<Sprite> obstacles)
{
	float dis = speed * delta_time;
	Sprite temp = spritesheet; 
	switch (dir) {
	case 0:
		temp.move(sf::Vector2f(0, -dis));
		break;
	case 1:
		temp.move(sf::Vector2f(0, dis));
		break;
	case 2:
		temp.move(sf::Vector2f(dis, 0));
		break;
	case 3:
		temp.move(sf::Vector2f(-dis, 0));
		break;
	}
	for (auto obstacle : obstacles)
		if (temp.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		{
			dis *= -1;
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
			return;
		}
	spritesheet = temp;
}



Object::Object(string path, Vector2u image_contain, float switch_time, float speed , Vector2f pos)
{
	if (!(texture.loadFromFile(path)))
	{
		cout << "Could Not Load File.." << endl;
	}
	this->path = path;
	this->speed = speed; 
	this->origin_speed = speed; 
	sprite.setTexture(texture);
	this->sprite.setPosition(pos);
	this->animation = Animation(&texture, image_contain, switch_time); 
}

void Object::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}


sf::Vector2f Object::getPosition() {
	sf::Vector2f pos = sprite.getPosition();
	pos.x += animation.uv_rect.width / 2;
	pos.y += animation.uv_rect.height / 2;
	return pos;
}

void Object::setPosition(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

sf::Vector2f Object::getSize()
{
	sf::Vector2f size;
	size.x = animation.uv_rect.width;
	size.y = animation.uv_rect.height;
	return size;
}

void Animation::loadAnimation(istream& in)
{
	in >> total_time >> switch_time; 
	in >> image_contain.x >> image_contain.y;
	in >> current_image.x >> current_image.y; 
	in >> uv_rect.top >> uv_rect.left >> uv_rect.width >> uv_rect.height;
}

Object::Object(istream& in)
{
	in >> path; 
	in >> speed >> origin_speed; 
	texture.loadFromFile(path); 
	sprite.setTexture(texture);

	
	float x, y; 
	in >> x >> y;
	this->sprite.setPosition(Vector2f(x , y));
	this->animation.loadAnimation(in);
}

void Animation::saveAnimation(ostream& out)
{
	out << total_time << ' ' << switch_time << '\n'; 
	out << image_contain.x << ' ' << image_contain.y << '\n'; 
	out << current_image.x << ' ' << current_image.y << '\n';
	out << uv_rect.top << ' ' << uv_rect.left << ' ' << uv_rect.width << ' ' << uv_rect.height << '\n'; 
}

void Object::saveObject(ostream& out)
{
	// path 
	out << path << '\n';
	// speed and origin speed 
	out << speed << ' ' << origin_speed << '\n';
	// save position 
	out << this->sprite.getPosition().x << ' ' << this->sprite.getPosition().y << '\n';
	this->animation.saveAnimation(out);

}
