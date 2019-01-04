#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "player.h"
#include "constVal.h"


class Monster
{
	friend class Player;
	friend class MainGame;
	friend class MonsterManager;
public:
	Monster() { ; }
	Monster(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead);
	~Monster() { ; }
	
	void onCollision(Player& l_player);
	void draw(sf::RenderWindow& l_window)const;
private:
	sf::Sprite m_monsterSprite;
	int m_xPos;
	int m_yPos;
	int m_floor;
	int m_exp;
	int m_hp;
	int m_def;
	int m_atk;
	int m_money;
	int type;
	bool isDead;
};

class MonsterManager
{
public:
	MonsterManager() { ; }
	MonsterManager(std::vector<std::vector<int>> &data, TextureManager &l_textures); // initialize every Monsters here
	void addMonster(Monsterid::ID monsterID, Monster& monsterEntity);
	Monster& findMonster(Monsterid::ID monsterID);

	void drawCurrentFloorMonster(sf::RenderWindow &l_window, const int currentFloor);
private:
	std::map <Monsterid::ID, std::unique_ptr<Monster>> monsterContainer;
};