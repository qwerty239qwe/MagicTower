#include "mainGame.h"


MainGame::MainGame(TextureManager &l_textures, Player &l_player, FileManager &l_omniData, DialogBox &l_dialogBox, DialogBox &l_transactionBox, DialogBox &l_monsInfoBox, sf::Font& l_EnglishFont, sf::Font& l_ChineseFont) :
	xPlayerPos(5), yPlayerPos(9), 
	sleepTime(sf::seconds(0.005)), 
	mDialogBox(l_dialogBox), mTransactionBox(l_transactionBox), mMonsInfoBox(l_monsInfoBox),
	mEnglishFont(l_EnglishFont), mChineseFont(l_ChineseFont), mFloor(0)
{
	
	mOmniData = &l_omniData;
	mNPCdata = mOmniData->getNPCData();
	mMonsterData = mOmniData->getMonsterData();
	mTileData = mOmniData->getTileData();
	mTextures = &l_textures;
	mNPCs = NPCmanager(mNPCdata, *mTextures);
	mMons = MonsterManager(mMonsterData, *mTextures);
	mTiles = TileManager(mTileData, *mTextures);
	mPlayer = &l_player;
	setObjPosition(mPlayer->p_playerSprite, xPlayerPos, yPlayerPos);
	mPlayer->p_playerSprite.setTexture(mTextures->get(Textures::Teacher), true);
	mPlayer->p_playerSprite.setScale(sf::Vector2f(2, 2));
	mPlayer->p_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(40, 40)));
	mMap.setTexture(mTextures->get(Textures::Map));
}

void MainGame::processEvents(sf::RenderWindow& l_window, const sf::Time &timePast)
{
	if (mDialogBox.getState())
	{
		mDialogBox.processEvent(l_window);

	} 
	else if (mTransactionBox.getState())
	{
		mTransactionBox.processEvent(l_window);
	}
	else
	{
		sf::Event event;

		while (l_window.pollEvent(event))
		{
			timeSinceLastKeyPressed += timePast;
			while (timeSinceLastKeyPressed >= sleepTime)
			{
				timeSinceLastKeyPressed -= sleepTime;
				mIsCoolingDown = false;
			}

			if (event.type == sf::Event::Closed)
				l_window.close();
			else if (event.type == sf::Event::KeyPressed && !mPlayer->isPlayerDead)
			{
				handlePlayerInput(event.key.code, true);
			}
		}
	}
}

void MainGame::update()
{
	setObjPosition(mPlayer->p_playerSprite, xPlayerPos, yPlayerPos);
}

void MainGame::render(sf::RenderWindow &l_window)
{
	l_window.clear();
	l_window.draw(mMap);
	renderAttributes(l_window);
	mPlayer->draw(l_window);
	mNPCs.drawCurrentFloorNPC(l_window, mFloor);
	mMons.drawCurrentFloorMonster(l_window, mFloor);
	mTiles.drawCurrentFloorTile(l_window, mFloor);
	if (mDialogBox.getState())
	{
		mDialogBox.renderDialogBox(l_window, false);
	}
	if (mTransactionBox.getState())
	{
		mTransactionBox.renderDialogBox(l_window, false);
	}
	if (mIsDisplayingMonsInfo)
	{
		mMonsInfoBox.renderDialogBox(l_window, mMons, mMons.getMonsterType(mFloor), *mPlayer);
	}

	l_window.display();
}

void MainGame::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (!mIsCoolingDown)
	{
		if ((key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left || key == sf::Keyboard::Right) && !mIsDisplayingMonsInfo)
		{
			mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::Walk));
			mSoundPlayer.play();
			mIsCoolingDown = true;
			if (key == sf::Keyboard::Up)
			{
				mPlayer->p_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(12 * 44, 0), sf::Vector2i(44, 44)));
				if (!isCollide(0, -1))
				{
					yPlayerPos--;
				}
			}
			else if (key == sf::Keyboard::Down)
			{
				mPlayer->p_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(0 * 44, 0), sf::Vector2i(44, 44)));
				if (!isCollide(0, 1))
				{
					yPlayerPos++;
				}
			}
			else if (key == sf::Keyboard::Left)
			{
				mPlayer->p_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(4 * 44, 0), sf::Vector2i(44, 44)));
				if (!isCollide(-1, 0))
				{
					xPlayerPos--;
				}
			}
			else if (key == sf::Keyboard::Right)
			{
				mPlayer->p_playerSprite.setTextureRect(sf::IntRect(sf::Vector2i(8 * 44, 0), sf::Vector2i(44, 44)));
				if (!isCollide(1, 0))
				{
					xPlayerPos++;
				}
			}
		}
		
	
		if (key == sf::Keyboard::M)
		{
			// adjust sound volume
			if (mSoundPlayer.getVolume() - 25.f >= 0.f)
				mSoundPlayer.setVolume(mSoundPlayer.getVolume() - 25.f);
			else 
				mSoundPlayer.setVolume(100.f);
		}
		else if (key == sf::Keyboard::I)
		{
			mIsDisplayingMonsInfo = !mIsDisplayingMonsInfo;
		}
	}
}


bool MainGame::isPlayerAlive()
{
	if (mPlayer->isPlayerDead)
	{
		mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::Dead));
		mSoundPlayer.play();
	}
		
	return !mPlayer->isPlayerDead;
}

void MainGame::setObjPosition(sf::Sprite& obj, float xPosIndex, float yPosIndex)
{
	obj.setPosition(xPosIndex *GRID_LEN, yPosIndex *GRID_LEN);
}

bool MainGame::isCollide(int deltaX, int deltaY)
{
	if ((xPlayerPos + deltaX <= 0) || (xPlayerPos + deltaX >= 10) || (yPlayerPos + deltaY <= 0) || (yPlayerPos + deltaY >= 10))
	{
		return true;
	}
	
	
	for (int npcID = NPCid::NPC1; npcID != NPCid::NPC12; ++npcID)
	{
		if (xPlayerPos + deltaX == mNPCdata[npcID][0] && yPlayerPos + deltaY == mNPCdata[npcID][1] && mFloor == mNPCdata[npcID][2] && !mNPCs.findNPC(static_cast<NPCid::ID>(npcID)).isDead)
		{
			// deal with NPC dialogs
			if (mNPCdata[npcID][4] == 1)
				mNPCs.findNPC(static_cast<NPCid::ID>(npcID)).onCollision(*mPlayer, mDialogBox);
			else if (mNPCdata[npcID][4] == 2)
				mNPCs.findNPC(static_cast<NPCid::ID>(npcID)).onCollision(*mPlayer, mTransactionBox);
			
			return true;
		}
	}
	// deal with Monster
	for (int monsterID = Monsterid::Monster1; monsterID != Monsterid::Monster60; ++monsterID)
	{
		if (xPlayerPos + deltaX == mMonsterData[monsterID][0] && yPlayerPos + deltaY == mMonsterData[monsterID][1] && mFloor == mMonsterData[monsterID][2] && !mMons.findMonster(static_cast<Monsterid::ID>(monsterID)).isDead)
		{
			mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::Battle));
			mSoundPlayer.play();
			mMons.findMonster(static_cast<Monsterid::ID>(monsterID)).onCollision(*mPlayer);
			return true;
		}
	}
	// deal with Others
	for (int tileID = TileID::Wall1; tileID != TileID::Downstair10; ++tileID)
	{
		if (xPlayerPos + deltaX == mTileData[tileID][0] && yPlayerPos + deltaY == mTileData[tileID][1] && mFloor == mTileData[tileID][2] && !mTiles.findTile(static_cast<TileID::ID>(tileID)).isDead)
		{
			mTiles.findTile(static_cast<TileID::ID>(tileID)).onCollision(*mPlayer, mFloor);
			if (mTileData[tileID][4] == 7)
			{
				mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::Upstair));
				mSoundPlayer.play();
				setDownStairPosition();
			}
			else if (mTileData[tileID][4] == 8)
			{
				mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::Upstair));
				mSoundPlayer.play();
				setUpStairPosition();
			}
			else if (mTileData[tileID][4] <= 3 && mTileData[tileID][4] > 0) // Open Doors
			{
				mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::OpenDoor));
				mSoundPlayer.play();
			}
			else if (mTileData[tileID][4] > 3 && mTileData[tileID][4] != 11) // Get Items
			{
				mSoundPlayer.setBuffer(mSoundBuffer.get(Sound::GetItem));
				mSoundPlayer.play();
			}
			return true;
		}
	}

	return false;
}

void MainGame::renderAttributes(sf::RenderWindow& l_window)
{
	sf::Text hpHeader("HP : ", mEnglishFont, FONT_SIZE);
	sf::Text atkHeader("ATK : ", mEnglishFont, FONT_SIZE);
	sf::Text defHeader("DEF : ", mEnglishFont, FONT_SIZE);
	sf::Text lvlHeader("LVL : ", mEnglishFont, FONT_SIZE);
	sf::Text expHeader("EXP : ", mEnglishFont, FONT_SIZE);
	sf::Text floorHeader("Floor : ", mEnglishFont, FONT_SIZE);
	sf::Sprite yellowKeyHeader(mTextures->get(Textures::YellowKey));
	sf::Sprite blueKeyHeader(mTextures->get(Textures::BlueKey));
	sf::Sprite redKeyHeader(mTextures->get(Textures::RedKey));
	yellowKeyHeader.setScale(0.5, 0.5);
	blueKeyHeader.setScale(0.5, 0.5);
	redKeyHeader.setScale(0.5, 0.5);
	sf::Text moneyHeader("Money : ", mEnglishFont, FONT_SIZE);

	sf::Text hpValue(std::to_string(mPlayer->p_hp), mEnglishFont, FONT_SIZE);
	sf::Text atkValue(std::to_string(mPlayer->p_atk), mEnglishFont, FONT_SIZE);
	sf::Text defValue(std::to_string(mPlayer->p_def), mEnglishFont, FONT_SIZE);
	sf::Text lvlValue(std::to_string(mPlayer->p_level), mEnglishFont, FONT_SIZE);
	sf::Text expValue(std::to_string(mPlayer->p_exp), mEnglishFont, FONT_SIZE);
	sf::Text floorValue(std::to_string(mFloor), mEnglishFont, FONT_SIZE);
	sf::Text yellowKeyValue(std::to_string(mPlayer->p_yellowKeys), mEnglishFont, FONT_SIZE);
	sf::Text blueKeyValue(std::to_string(mPlayer->p_blueKeys), mEnglishFont, FONT_SIZE);
	sf::Text redKeyValue(std::to_string(mPlayer->p_redKeys), mEnglishFont, FONT_SIZE);
	sf::Text moneyValue(std::to_string(mPlayer->p_money), mEnglishFont, FONT_SIZE);

	hpHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 1 * GRID_LEN));
	atkHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 2 * GRID_LEN));
	defHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 3 * GRID_LEN));
	lvlHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 4 * GRID_LEN));
	expHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 5 * GRID_LEN));
	yellowKeyHeader.setPosition(sf::Vector2f(13 * GRID_LEN, 6 * GRID_LEN));
	blueKeyHeader.setPosition(sf::Vector2f(13 * GRID_LEN, 7 * GRID_LEN));
	redKeyHeader.setPosition(sf::Vector2f(13 * GRID_LEN, 8 * GRID_LEN));
	moneyHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 9 * GRID_LEN));
	floorHeader.setPosition(sf::Vector2f(12 * GRID_LEN, 10 * GRID_LEN));

	hpValue.setPosition(sf::Vector2f(14 * GRID_LEN, 1 * GRID_LEN));
	atkValue.setPosition(sf::Vector2f(14 * GRID_LEN, 2 * GRID_LEN));
	defValue.setPosition(sf::Vector2f(14 * GRID_LEN, 3 * GRID_LEN));
	lvlValue.setPosition(sf::Vector2f(14 * GRID_LEN, 4 * GRID_LEN));
	expValue.setPosition(sf::Vector2f(14 * GRID_LEN, 5 * GRID_LEN));
	yellowKeyValue.setPosition(sf::Vector2f(14 * GRID_LEN, 6 * GRID_LEN));
	blueKeyValue.setPosition(sf::Vector2f(14 * GRID_LEN, 7 * GRID_LEN));
	redKeyValue.setPosition(sf::Vector2f(14 * GRID_LEN, 8 * GRID_LEN));
	moneyValue.setPosition(sf::Vector2f(14 * GRID_LEN, 9 * GRID_LEN));
	floorValue.setPosition(sf::Vector2f(14 * GRID_LEN, 10 * GRID_LEN));

	l_window.draw(hpHeader);
	l_window.draw(atkHeader);
	l_window.draw(defHeader);
	l_window.draw(lvlHeader);
	l_window.draw(expHeader);
	l_window.draw(yellowKeyHeader);
	l_window.draw(blueKeyHeader);
	l_window.draw(redKeyHeader);
	l_window.draw(moneyHeader);
	l_window.draw(floorHeader);

	l_window.draw(hpValue);
	l_window.draw(atkValue);
	l_window.draw(defValue);
	l_window.draw(lvlValue);
	l_window.draw(expValue);
	l_window.draw(yellowKeyValue);
	l_window.draw(blueKeyValue);
	l_window.draw(redKeyValue);
	l_window.draw(moneyValue);
	l_window.draw(floorValue);
}

void MainGame::setDownStairPosition()
{
	switch (mFloor)
	{
	case (0):
		xPlayerPos = 5;
		yPlayerPos = 2;
		break;
	case (1):
		xPlayerPos = 8;
		yPlayerPos = 1;
		break;
	case 2:
		xPlayerPos = 9;
		yPlayerPos = 8;
		break;
	case 3:
		xPlayerPos = 2;
		yPlayerPos = 9;
		break;
	case 4:
		xPlayerPos = 1;
		yPlayerPos = 2;
		break;
	case 5:
		xPlayerPos = 1;
		yPlayerPos = 8;
		break;
	case 6:
		xPlayerPos = 2;
		yPlayerPos = 1;
		break;
	case 7:
		xPlayerPos = 6;
		yPlayerPos = 8;
		break;
	case 8:
		xPlayerPos = 9;
		yPlayerPos = 2;
		break;
	case 9:
		xPlayerPos = 1;
		yPlayerPos = 6;
		break;
	}
}

void MainGame::setUpStairPosition()
{
	switch (mFloor)
	{
	case (10):
		xPlayerPos = 5;
		yPlayerPos = 8;
		break;
	case (1):
		xPlayerPos = 4;
		yPlayerPos = 1;
		break;
	case 2:
		xPlayerPos = 9;
		yPlayerPos = 2;
		break;
	case 3:
		xPlayerPos = 8;
		yPlayerPos = 9;
		break;
	case 4:
		xPlayerPos = 2;
		yPlayerPos = 9;
		break;
	case 5:
		xPlayerPos = 2;
		yPlayerPos = 1;
		break;
	case 6:
		xPlayerPos = 1;
		yPlayerPos = 8;
		break;
	case 7:
		xPlayerPos = 2;
		yPlayerPos = 1;
		break;
	case 8:
		xPlayerPos = 5;
		yPlayerPos = 8;
		break;
	case 9:
		xPlayerPos = 9;
		yPlayerPos = 2;
		break;
	}
}

