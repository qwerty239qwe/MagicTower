#include "player.h"

Player::Player():
	p_floor(1), isPlayerDead(false),
	p_level(1), p_exp(0), p_atk(10), p_def(10), p_hp(100), p_money(100),
	p_yellowKeys(1), p_redKeys(1), p_blueKeys(1)
{
	isPlayerDead = false;
}

Player::Player(int& l_floor, int l_level, int l_exp, int l_atk,
	int l_def, int l_hp, int l_money, int l_yellowKeys, int l_redKeys, int l_blueKeys) :
	p_floor(l_floor), isPlayerDead(false),
	p_level(l_level), p_exp(l_exp), p_atk(l_atk), p_def(l_def), p_hp(l_hp), p_money(l_money),
	p_yellowKeys(l_yellowKeys), p_redKeys(l_redKeys), p_blueKeys(l_blueKeys)
{

}
bool Player::isDead()
{
	return isPlayerDead;
}

void Player::checkLevelUp()		// once player gains exp, check level
{
	while (p_exp >= p_level * 20)
	{
		p_level ++;
		p_atk += 10;
		p_def += 10;
		p_hp += 100;
		p_exp -= p_level * 20;
	}
}

void Player::draw(sf::RenderWindow &l_window) const
{
	l_window.draw(p_playerSprite);
}
