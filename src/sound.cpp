#include "sound.h"


BGMmanager::BGMmanager()
	: mBGM(),
	mVolume(100.f),
	mFilenames()
{
	mFilenames[BGM::menuBGM] = BGM_PATH + "BGM1.wav";
	mFilenames[BGM::mainBGM] = BGM_PATH + "main.ogg";
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
	load(Sound::menuBGM, "bookClose.ogg");
}

void SoundManager::load(Sound::ID id, const std::string &filename)
{
	sf::SoundBuffer tempSB;
	if (tempSB.loadFromFile(SOUND_PATH + filename))
		std::cout << filename << " is loaded";
	sf::Sound testSound;
	testSound.setBuffer(tempSB);
	testSound.play();
	std::unique_ptr <sf::Sound> sound(new sf::Sound);
	//sound->setBuffer(tempSB);
	//sound->play();
	mSoundStorage.insert(std::make_pair(id, std::move(sound)));
}

sf::Sound& SoundManager::get(Sound::ID id)
{
	auto found = mSoundStorage.find(id);
	return *found->second;
}

const sf::Sound& SoundManager::get(Sound::ID id) const
{
	auto found = mSoundStorage.find(id);
	return *found->second;
}