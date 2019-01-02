#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "mainGame.h"
#include "monster.h"
#include "game.h"
#include "common.h"


class Player
{
	friend class Monster;
public:
	Player() { ; }
	Player(Position p_position, int level, int exp, int atk, int def,
		   int hp, int money, int yellowKeys, int redKeys, int blueKeys);
	~Player() { ; }
	bool isDead(bool dead);
	
	sf::Sprite p_playerSprite;

	void draw(sf::RenderTarget& l_target)const;
private:
	Position p_position;

	int p_level;
	int p_exp;
	int p_hp;
	int p_atk;
	int p_def;
	int p_money;
	int p_yellowKeys;
	int p_redKeys;
	int p_blueKeys;
	
	


};