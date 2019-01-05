#include "sound.h"


BGMmanager::BGMmanager()
	: mBGM(),
	mVolume(100.f),
	mFilenames()
{
	mFilenames[BGM::menuBGM] = BGM_PATH + "menuBGM.ogg";
	mFilenames[BGM::mainBGM] = BGM_PATH + "mainBGM.ogg";
	mFilenames[BGM::EndBGM] = BGM_PATH + "mainBGM.ogg";
}

void BGMmanager::play(BGM::ID id)
{
	std::string BGMfileName = mFilenames[id];
	mBGM.openFromFile(BGMfileName);
	mBGM.setVolume(mVolume);
	mBGM.setLoop(true);
	mBGM.play();
}

void BGMmanager::stop()
{
	mBGM.stop();
}
void BGMmanager::togglePaused(bool isPaused)
{
	if (isPaused)
		mBGM.pause();
	else
		mBGM.play();
}
void BGMmanager::setVolume(float volume)
{
	mVolume = volume;
}


SoundManager::SoundManager()
{
	load(Sound::Walk, "walk.ogg");
	load(Sound::Battle, "battle.ogg");
	load(Sound::Upstair, "upstair.ogg");
	load(Sound::Dead, "dead.ogg");
}

void SoundManager::load(Sound::ID id, const std::string &filename)
{
	std::unique_ptr <sf::SoundBuffer> sound(new sf::SoundBuffer);
	sound->loadFromFile(SOUND_PATH + filename);
	mSoundStorage.insert(std::make_pair(id, std::move(sound)));
}

sf::SoundBuffer& SoundManager::get(Sound::ID id)
{
	auto found = mSoundStorage.find(id);
	return *found->second;
}

const sf::SoundBuffer& SoundManager::get(Sound::ID id) const
{
	auto found = mSoundStorage.find(id);
	return *found->second;
}