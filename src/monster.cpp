#include "monster.h"

Monster::Monster(Position l_position, int l_what, int l_type)
{
	m_position.x = l_position.x;
	m_position.y = l_position.y;
	m_position.z = l_position.z;
	what = l_what;
	type = l_type;
	switch (type)
	{
	case(1):
		m_exp = 1;
		m_hp = 36;
		m_def = 4;
		m_atk = 12;
		m_money = 5;
		break;
	case(2):
		m_exp = 1;
		m_hp = 10;
		m_def = 8;
		m_atk = 15;
		m_money = 4;
	case(3):
		m_exp = 2;
		m_hp = 42;
		m_def = 16;
		m_atk = 25;
		m_money = 4;
	case(4):
		m_exp = 2;
		m_hp = 32;
		m_def = 20;
		m_atk = 40;
		m_money = 15;
	case(5):
		m_exp = 8;
		m_hp = 105;
		m_def = 40;
		m_atk = 85;
		m_money = 80;
	default:
		m_exp = 100;
		m_hp = 50;
		m_def = 120;
		m_atk = 400;
		m_money = 400;
		break;
		
	}
}

void Monster::onCollision(Player& l_player)
{
	while (m_hp > 0)
	{
		if(l_player.p_atk - m_def > 0)
			m_hp -= (l_player.p_atk - m_def);
		if (m_hp > 0)
		{
			if (m_atk - l_player.p_def > 0)
				l_player.p_hp -= (m_atk - l_player.p_def);
		}
		if (l_player.p_hp <= 0)
		{
			l_player.p_isDead = true;
			break;
		}
	}
	if (m_hp <= 0)
	{
		what = 0;
		l_player.p_exp += m_exp;
		l_player.p_money += m_money;
	}
	//level up
	if (l_player.p_exp >= 70)
	{
		l_player.p_exp = 0;
		l_player.p_hp += 100;
		l_player.p_def += 10;
		l_player.p_atk += 10;
	}
}
void Monster::draw(sf::RenderTarget& l_target)const
{
	l_target.draw(m_monsterSprite);
}