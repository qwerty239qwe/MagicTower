#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "sound.h"
#include "constVal.h"
#include "dialogue.h"
#include "player.h"
#include "NPC.h"
#include "monster.h"
#include "tile.h"


class MainGame
{
public :
	MainGame() { ; }
	MainGame(TextureManager &l_textures, Player &l_player, FileManager &l_omniData ,DialogBox &l_dialogBox, DialogBox &l_transactionBox, sf::Font& l_EnglishFont, sf::Font& l_ChineseFont);
	void processEvents(sf::RenderWindow &l_window, const sf::Time &timePast);
	void update();
	void render(sf::RenderWindow &l_window);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	// Time
	sf::Time timeSinceLastKeyPressed = sf::Time::Zero;
	sf::Time sleepTime;

	// Container (textures, instances, data ...)
	TextureManager *mTextures;
	NPCmanager mNPCs;
	MonsterManager mMons;
	TileManager mTiles;
	std::vector<std::vector<int>> mNPCdata;
	std::vector<std::vector<int>> mMonsterData;
	std::vector<std::vector<int>> mTileData;
	DialogBox mDialogBox;
	DialogBox mTransactionBox;
	Player *mPlayer;
	FileManager *mOmniData;


	sf::Sprite mMap;
	sf::Font mEnglishFont;
	sf::Font mChineseFont;

	bool mIsCoolingDown;

	bool isCollide(int deltaX, int deltaY);
	int xPlayerPos;
	int yPlayerPos;
	int mFloor;
	void setObjPosition(sf::Sprite& obj, float xPosIndex, float yPosIndex);
	void renderAttributes(sf::RenderWindow& l_window);
	// void loadGame(bool loadExistGame);

};