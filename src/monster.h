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
	Monster(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead, 
		int l_hp, int l_atk, int l_def, int l_exp, int l_money);
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
	sf::Texture& findMonsterTexture(Monsterid::Type monsterType);
	void drawCurrentFloorMonster(sf::RenderWindow &l_window, const int currentFloor);
	std::vector<Monsterid::Type> getMonsterType(const int currentFloor);
	std::vector<int> getMonsterValue(Monsterid::Type monsterType);
	int calculateExpectedDamage(Player &l_player, Monsterid::Type monsterType);
private:
	std::map <Monsterid::ID, std::unique_ptr<Monster>> monsterContainer;
	std::map <Monsterid::Type, std::unique_ptr<sf::Texture>> monsterTextures;
	std::map <Monsterid::Type, std::vector<int>> monsterValue;							// hp, atk, def, exp, mny
	void addMonsterType(Monsterid::Type monsterType, sf::Texture& monsterTexture);

};