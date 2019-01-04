#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "menu.h"
#include "mainGame.h"
#include "sound.h"
#include "dialogue.h"
#include "player.h"
#include "constVal.h"


namespace Screen
{
	enum ID { MainMenu, MainGame, Infomation, EndScreen };
}

class Game {
public :
	Game();
	void run();

private:
	
	sf::RenderWindow mWindow;
	sf::Sprite mBGSprite;
	sf::Sprite mDBBig;
	sf::Sprite mDBMedium;
	sf::Sprite mDBSmall;
	sf::Font mEnglishFont;
	sf::Font mChineseFont;
	Screen::ID mCurrentScreen;
	
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	TextureManager mTextures;
	
};