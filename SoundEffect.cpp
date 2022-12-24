#include "SoundEffect.h"


void SoundEffect::init(const string& path_sound) {
	if (!this->buffer.loadFromFile(path_sound)) {
		cout << "COULD NOT LOAD SOUND EFFECT " << path_sound << endl;
		return;
	}
	this->sound.setBuffer(this->buffer);
}

void SoundEffect::play() {
	this->sound.play();
}

bool SoundEffect::isPlaying() {
	return sound.Playing;
}