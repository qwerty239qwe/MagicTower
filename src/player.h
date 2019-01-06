#pragma once
#include <SFML/Graphics.hpp>



class Player
{
	friend class Monster;
	friend class MainGame;
	friend class NPC;
	friend class DialogBox;
	friend class Tile;
	friend class MonsterManager;
public:
	Player();
	Player(int level, int exp, int atk, int def,
		   int hp, int money, int yellowKeys, int redKeys, int blueKeys);
	
	void draw(sf::RenderWindow &l_window) const;
	
	
private:
	sf::Sprite p_playerSprite;
	
	int p_level;
	int p_exp;
	int p_hp;
	int p_atk;
	int p_def;
	int p_money;
	int p_yellowKeys;
	int p_redKeys;
	int p_blueKeys;
	bool isPlayerDead;

	void checkLevelUp();
};