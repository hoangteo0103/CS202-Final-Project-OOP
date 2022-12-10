#include "CMap.h"


using namespace std;

CMap::CMap(string dir) {
	if (!texture.loadFromFile(dir)) {
		cout << "Could Not Load Map" << endl;
	}

	sprite.setTexture(texture);
	size = texture.getSize();
}


void CMap::init(string dir)
{
	if (!texture.loadFromFile(dir)) {
		cout << "Could Not Load Map" << endl;
	}

	sprite.setTexture(texture);
	size = texture.getSize();
}

void CMap::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}



sf::Vector2u CMap::getSize() const{
	return size;
}