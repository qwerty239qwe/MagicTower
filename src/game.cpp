#include "game.h"

Game::Game()
	:mWindow(sf::VideoMode(window_width, window_height), "Jay's Adventures", sf::Style::Close),
	mTextures(), mBGSprite(), mDBBig(), mDBMedium(), mDBSmall(), mCurrentScreen(Screen::MainMenu)
{
	mEnglishFont.loadFromFile(FONT_PATH + "pixelfont.ttf");
	mChineseFont.loadFromFile(FONT_PATH + "pixelchifont.otf");
	mBGSprite.setTexture(mTextures.get(Textures::BackGround));
	mDBBig.setTexture(mTextures.get(Textures::DialogBig));
	mDBMedium.setTexture(mTextures.get(Textures::DialogMedium));
	mDBSmall.setTexture(mTextures.get(Textures::DialogSmall));
	mDBSmall.setPosition(0, window_height - mTextures.get(Textures::DialogSmall).getSize().y);
	mDBMedium.setPosition(0, window_height - mTextures.get(Textures::DialogMedium).getSize().y);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	BGMmanager bgm;
	Menu mainMenu(mBGSprite, mEnglishFont, sf::Color::Black, sf::Color::White, bgm);
	
	// gameOver info
	sf::Text gameOverTxt("Game Over", mEnglishFont, 100);
	gameOverTxt.setFillColor(sf::Color(150, 50, 50));
	gameOverTxt.setOutlineThickness(5);
	gameOverTxt.setOutlineColor(sf::Color::White);
	gameOverTxt.setPosition(4 * GRID_LEN, 4 * GRID_LEN);

	//test info
	std::string firstLine = "This line shall be printed";
	std::string secondLine = "This line shall not be printed";
	std::string name = "Introduction";
	std::vector<std::string> strvec;
	strvec.push_back(firstLine);
	strvec.push_back(secondLine);
	DialogBox infoDialog(mWindow, name, strvec, mDBBig, mEnglishFont, mChineseFont);
	DialogBox inGameDialog(mWindow, name, strvec, mDBSmall, mEnglishFont, mChineseFont);
	DialogBox inGameTransaction(mWindow, name, strvec, mDBMedium, mEnglishFont, mChineseFont);

	// main game
	int mFloor = 1;
	Player mPlayer(mFloor, 1, 0, 10, 10, 100, 1000, 1, 1, 1);
	MainGame* mainGame = new MainGame;
	FileManager* omniData = new FileManager;

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
					*omniData = FileManager("monsterFile.csv", "npcFile.csv",  "tileFile.csv");
					*mainGame = MainGame(mTextures, mPlayer, *omniData, inGameDialog, inGameTransaction, mEnglishFont, mChineseFont);
					mCurrentScreen = Screen::MainGame;
					bgm.stop();
					bgm.play(BGM::mainBGM);
				}
				else if (mainMenu.getActiveID() == 1)
				{
					*omniData = FileManager("monsterFile_save.csv", "npcFile_save.csv",  "tileFile_save.csv");
					*mainGame = MainGame(mTextures, mPlayer, *omniData, inGameDialog, inGameTransaction, mEnglishFont, mChineseFont);
					mCurrentScreen = Screen::MainGame;
					bgm.stop();
					bgm.play(BGM::mainBGM);
				}
				else if (mainMenu.getActiveID() == 2)
				{
					mCurrentScreen = Screen::Infomation;
					infoDialog.setState(true);
				}
			}
			mainMenu.render(mWindow);
			break;
		case (Screen::MainGame):
			
			mainGame->processEvents(mWindow, timeSinceLastUpdate);
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				mainGame->processEvents(mWindow, timeSinceLastUpdate);
				timeSinceLastUpdate -= TimePerFrame;
				if (!mainGame->isPlayerAlive())
				{
					mCurrentScreen = Screen::EndScreen;
				}
				
				mainGame->update();
				
			}
			

			mainGame->render(mWindow);
			
			break;
		case (Screen::Infomation):
			infoDialog.processEvent(mWindow);
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				infoDialog.processEvent(mWindow);
				if (infoDialog.getState() == false)
				{
					mCurrentScreen = Screen::MainMenu;
					mainMenu.resetActiveID();
				}
			}
			infoDialog.renderDialogBox(mWindow, true);
			break;
		case (Screen::EndScreen):
			timeSinceLastUpdate += clock.restart();
			sf::Event event;

			while (mWindow.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					mWindow.close();
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						mainMenu.resetActiveID();
						mCurrentScreen = Screen::MainMenu;
					}
						
				}
				
			}
			mWindow.clear();
			mWindow.draw(gameOverTxt);
			mWindow.display();
			break;
		}
	}
}

