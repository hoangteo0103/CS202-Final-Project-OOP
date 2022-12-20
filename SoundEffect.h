#pragma once
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
using namespace std;
class SoundEffect
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

public:
	
	void init(const string& path_sound);
	void play();
	bool isPlaying();
};



