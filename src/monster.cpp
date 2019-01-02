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
		m_exp = 2;
		m_hp = 20;
		m_def = 5;
		m_atk = 15;
		m_money = 1;
		break;
	default:
		m_exp = 3;
		m_hp = 50;
		m_def = 30;
		m_atk = 10;
		m_money = 2;
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
	}
	what = 0;
}
void Monster::draw(sf::RenderTarget& l_target)const
{
	l_target.draw(m_monsterSprite);
}