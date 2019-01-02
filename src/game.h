#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "menu.h"
#include "mainGame.h"

const int window_width = 1430, window_height = 880;
const std::string SPRITE_PATH = ".\/resources\/sprites\/";
const std::string FONT_PATH = ".\/resources\/font\/";



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
	sf::Font mEnglishFont;
	sf::Font mChineseFont;
	Screen::ID mCurrentScreen;
	
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	TextureManager mTextures;
};