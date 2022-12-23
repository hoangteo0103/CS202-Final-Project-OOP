#include "SoundEffect.h"


void SoundEffect::init(const string& path_sound) {
	std::cout << "In SoundEffect::init(), line: " << __LINE__ << '\n';
	if (!this->buffer.loadFromFile(path_sound)) {
		cout << "COULD NOT LOAD SOUND EFFECT " << path_sound << endl;
		return;
	}
	this->sound.setBuffer(this->buffer);
}

void SoundEffect::play() {
	std::cout << "In SoundEffect::play(), line: " << __LINE__ << '\n';
	this->sound.play();
}

bool SoundEffect::isPlaying() {
	std::cout << "In SoundEffect::isPlaying(), line: " << __LINE__ << '\n';
	return sound.Playing;
}