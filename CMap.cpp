#include "CMap.h"


using namespace std;

CMap::CMap(string dir) {
	std::cout << "In CMap::CMap(), line: " << __LINE__ << '\n';
	if (!texture.loadFromFile(dir)) {
		cout << "Could Not Load Map" << endl;
	}

	sprite.setTexture(texture);
	size = texture.getSize();
}


void CMap::init(string dir)
{
	std::cout << "In CMap::init(), line: " << __LINE__ << '\n';
	if (!texture.loadFromFile(dir)) {
		cout << "Could Not Load Map" << endl;
	}

	sprite.setTexture(texture);
	size = texture.getSize();
}

void CMap::draw(sf::RenderWindow& window) {
	std::cout << "In CMap::draw(), line: " << __LINE__ << '\n';
	window.draw(sprite);
}



sf::Vector2u CMap::getSize() const{
	std::cout << "In CMap::getSize(), line: " << __LINE__ << '\n';
	return size;
}