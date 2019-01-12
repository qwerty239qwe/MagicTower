#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "texture.h"
#include "menu.h"
#include "mainGame.h"
#include "sound.h"
#include "dialogue.h"
#include "player.h"
#include "initialize.h"


namespace Screen
{
	enum ID { MainMenu, MainGame, Infomation, Credits, EndScreen };
}

class Game {
public :
	Game();
	void run();

private:

	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::RenderWindow mWindow;
	
	// current screen
	Screen::ID mCurrentScreen;
	
	// textures manager
	TextureManager mTextures;

	// Dialogs sprites and fonts
	sf::Sprite mBGSprite;
	sf::Sprite mDBBig;
	sf::Sprite mDBMedium;
	sf::Sprite mDBSmall;
	std::vector<sf::Sprite> mAuthorPics;
	sf::Font mEnglishFont;
	sf::Font mChineseFont;
};