#pragma once
#include <SFML/Audio.hpp>
#include <cstring>
#include <iostream>
#include <map>
#include "constVal.h"

namespace BGM
{
	enum ID {
		menuBGM, mainBGM, EndBGM
	};
}

namespace Sound
{
	enum ID {
		Walk, Battle, Upstair, Dead
	};
}

class BGMmanager
{
public:
	BGMmanager();
	void play(BGM::ID id);
	void stop();
	void togglePaused(bool paused);
	void setVolume(float volume);
	
private:
	sf::Music mBGM;
	std::map<BGM::ID, std::string> mFilenames;
	float mVolume;
};

class SoundManager
{
public:
	SoundManager();
	void load(Sound::ID id, const std::string &filename);
	sf::SoundBuffer& get(Sound::ID id);
	const sf::SoundBuffer& get(Sound::ID id) const;
private:
	std::map <Sound::ID, std::unique_ptr<sf::SoundBuffer>> mSoundStorage;
};
