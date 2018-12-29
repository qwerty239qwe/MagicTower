#include "game.h"

Game::Game()
	:mWindow(sf::VideoMode(window_width, window_height), "Jay's Adventures", sf::Style::Close),
	mTextures(), mBGSprite(), mCurrentScreen(Screen::MainMenu)
{
	mTextures.load(Textures::Teacher, SPRITE_PATH + "heyTeacher.png");
	mTextures.load(Textures::BackGround, SPRITE_PATH + "testBG.jpg");
	mEnglishFont.loadFromFile(FONT_PATH + "pixelfont.ttf");
	mBGSprite.setTexture(mTextures.get(Textures::BackGround));
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	Menu mainMenu(mBGSprite, mEnglishFont, sf::Color::Black, sf::Color::White);
	MainGame mainGame(mTextures);
	while (mWindow.isOpen())
	{
		switch (mCurrentScreen)
		{
		case(Screen::MainMenu):

			mainMenu.processEvent(mWindow);
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				mainMenu.processEvent(mWindow);
				if (mainMenu.getActiveID() == 0)
				{
					mCurrentScreen = Screen::MainGame;
				}
			}
			mainMenu.render(mWindow);
			break;
		case (Screen::MainGame):
			mainGame.processEvents(mWindow);
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				mainGame.processEvents(mWindow);
				mainGame.update(TimePerFrame);
			}
			mainGame.render(mWindow);
			break;
		case (Screen::Infomation):
			break;
		case (Screen::EndScreen):
			break;
		}
		
	}
}
