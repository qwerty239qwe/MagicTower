#pragma once
#include <SFML/Graphics.hpp>
#include "mainGame.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "common.h"


class Monster
{
	friend class Player;
public:
	
	Monster(Position l_position, int l_what, int l_type);

	~Monster() { ; }
	
	sf::Sprite m_monsterSprite;

	void onCollision(Player& l_player);
	void draw(sf::RenderTarget& l_target)const;
private:
	Position m_position;
	int m_exp;
	int m_hp;
	int m_def;
	int m_atk;
	int m_money;
	int what;
	int type;

};