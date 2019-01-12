#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "player.h"
#include "initialize.h"

class Tile
{
	friend class TileManager;
	friend class MainGame;
public:
	Tile() { ; }
	Tile(int l_level, int l_xPos, int l_yPos,  int l_type, int l_isDead);
	~Tile() { ; }

	void onCollision(Player& l_player, int &floor);
	void draw(sf::RenderWindow& l_window) const;
private:
	sf::Sprite t_tileSprite;
	int t_floor;
	int t_xPos;
	int t_yPos;
	int type;
	bool isDead;
};

class TileManager
{
public:
	TileManager() { ; }
	TileManager(std::vector<std::vector<int>> &data, TextureManager &l_textures); // initialize every NPC here
	void addTile(TileID::ID tileID, Tile& tileEntity);
	Tile& findTile(TileID::ID tileID);

	void drawCurrentFloorTile(sf::RenderWindow &l_window, const int currentFloor);
private:
	std::map <TileID::ID, std::unique_ptr<Tile>> tileContainer;
};