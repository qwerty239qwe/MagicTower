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
	//time
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// bgm
	BGMmanager bgm;
	Menu mainMenu(mBGSprite, mEnglishFont, sf::Color::Color(50, 50, 50, 150), sf::Color::Color(180, 50, 50,255), bgm);
	
	// gameOver info
	sf::Text gameOverTxt("Game Over", mEnglishFont, 100);
	gameOverTxt.setFillColor(sf::Color(150, 50, 50));
	gameOverTxt.setOutlineThickness(5);
	gameOverTxt.setOutlineColor(sf::Color::White);
	gameOverTxt.setPosition(4 * GRID_LEN, 4 * GRID_LEN);

	//credits / info

	sf::Sprite pic1(mTextures.get(Textures::Slime));
	sf::Sprite pic2(mTextures.get(Textures::NPC));
	sf::Sprite pic3(mTextures.get(Textures::Pikachu));
	sf::Sprite pic4(mTextures.get(Textures::GitCat));
	mAuthorPics = { pic1, pic2, pic3, pic4 };

	std::string authors = "Yu-De Lin \t Programming | Design \n\nEn-Ching \t Present\n\nEn-Ching \t Present";
	std::vector<std::string> creditsStrvec = {"Yu-De Lin\n", 
		"Jerry Chen\n" , 
		"Mathew chiang\n" , 
		"Yu-De Lin \n" };
	
	std::vector<sf::String> creditsStrvecWork = { L"\u7f8e\u8853\u8a2d\u8a08\n\u7a0b\u5f0f\u8a2d\u8a08", 
		L"\u4f01\u5283\n\u7a0b\u5f0f\u8a2d\u8a08", 
		L"\u5c0b\u627e\u97f3\u6548\u7d20\u6750\n\u7a0b\u5f0f\u8a2d\u8a08",
		L"\u4e0a\u53f0\u5831\u544a\n\u7a0b\u5f0f\u8a2d\u8a08"};

	std::vector<sf::String> infoStrvec = { L"\n\n\n            \u63a7\u5236\u89d2\u8272\uff1a\u9375\u76e4\u7684\u4e0a\u4e0b\u5de6\u53f3\u9375\n\n\n\n            \u9078\u64c7 \/ \u8df3\u904e\u5c0d\u8a71\uff1a\u7a7a\u767d\u9375\n\n\n\n            \u67e5\u770b\u602a\u7269\u5c6c\u6027\uff1aI"};
	

	DialogBox infoDialog(mWindow, mDBBig, mEnglishFont, mChineseFont);
	DialogBox creditsDialog(mWindow, mDBBig, mEnglishFont, mChineseFont, mAuthorPics);
	DialogBox monsInfoDialog(mWindow, mDBBig, mEnglishFont, mChineseFont);
	DialogBox inGameDialog(mWindow, mDBSmall, mEnglishFont, mChineseFont);
	DialogBox inGameTransaction(mWindow, mDBMedium, mEnglishFont, mChineseFont);

	infoDialog.setDialog(infoStrvec, true);
	creditsDialog.setDialog(creditsStrvec, false);
	creditsDialog.setDialog(creditsStrvecWork, true);
	// main game
	Player mPlayer(1, 0, 10, 10, 100, 1000, 1, 1, 1);

	

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
					mPlayer = Player(1, 0, 10, 10, 100, 1000, 1, 1, 1);
					*mainGame = MainGame(mTextures, mPlayer, *omniData, inGameDialog, inGameTransaction, monsInfoDialog, mEnglishFont, mChineseFont);
					mCurrentScreen = Screen::MainGame;
					bgm.stop();
					bgm.play(BGM::mainBGM);
				}
				else if (mainMenu.getActiveID() == 1)
				{
					mCurrentScreen = Screen::Infomation;
					infoDialog.setState(true);
				}
				else if (mainMenu.getActiveID() == 2)
				{
					mCurrentScreen = Screen::Credits;
					creditsDialog.setState(true);
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
		case (Screen::Credits):
			creditsDialog.processEvent(mWindow);
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				creditsDialog.processEvent(mWindow);
				if (creditsDialog.getState() == false)
				{
					mCurrentScreen = Screen::MainMenu;
					mainMenu.resetActiveID();
				}
			}
			creditsDialog.renderDialogBox(mWindow, true);
			break;
		case (Screen::EndScreen):
			bgm.stop();
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
						bgm.stop();
						bgm.play(BGM::menuBGM);
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

