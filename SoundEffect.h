#pragma once
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class SoundEffect
{
private:
	SoundBuffer buffer;
	Sound sound;

public:
	void init(const string& path_sound);
	void play();
	bool isPlaying();
	void setVolume(int vol);
};



