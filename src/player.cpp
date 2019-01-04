#include "player.h"
#include "mainGame.h"
#include "texture.h"

Player::Player(Position l_position, int l_level, int l_exp, int l_atk, 
	int l_def, int l_hp, int l_money, int l_yellowKeys, int l_redKeys,
	int l_blueKeys)
{
	
	p_position.x = l_position.x;
	p_position.y = l_position.y;
	p_position.z = l_position.z;
	p_level = l_level;
	p_exp = l_exp;
	p_atk = l_atk;
	p_def = l_def;
	p_hp = l_hp;
	p_money = l_money;
	p_yellowKeys = l_yellowKeys;
	p_redKeys = l_redKeys;
	p_blueKeys = l_blueKeys;
	p_isDead = false;
}


