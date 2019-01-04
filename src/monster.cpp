#include "monster.h"

Monster::Monster(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead):
	m_floor(l_floor), type(l_type), 
	m_xPos(l_xPos), m_yPos(l_yPos), isDead(!static_cast<bool>(l_isDead))
{
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
		m_atk = 15;
		m_money = 2;
		break;
	}
}

void Monster::onCollision(Player& l_player)
{
	if (l_player.p_atk - m_def <= 0 && m_atk - l_player.p_def <= 0)
	{
		return;
	}
	while (m_hp > 0)
	{
		if(l_player.p_atk - m_def > 0)
			m_hp -= (l_player.p_atk - m_def);
		if (m_hp > 0 && m_atk - l_player.p_def > 0)
		{
			l_player.p_hp -= (m_atk - l_player.p_def);
			if (l_player.p_hp <= 0)
			{
				l_player.isPlayerDead = true;
			}
		}
	}
	l_player.p_exp += m_exp;
	l_player.checkLevelUp();
	l_player.p_money += m_money;
	isDead = true;
}
void Monster::draw(sf::RenderWindow& l_window)const
{
	l_window.draw(m_monsterSprite);
}

MonsterManager::MonsterManager(std::vector<std::vector<int>> &data, TextureManager &l_textures)
{
	std::vector<Monster> monsterVec(countMonster);

	for (int monsterID = Monsterid::Monster1; monsterID != Monsterid::Monster60; ++monsterID)
	{
		monsterVec[monsterID] = Monster(data[monsterID][2], data[monsterID][0], data[monsterID][1], data[monsterID][4], data[monsterID][3]);
		switch (data[monsterID][4])
		{
		case 1:
			monsterVec[monsterID].m_monsterSprite.setTexture(l_textures.get(Textures::Slime));
		default:
			monsterVec[monsterID].m_monsterSprite.setTexture(l_textures.get(Textures::Slime2));
		}
		
		//npcVec[npcID].n_npcSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(40, 40)));
		monsterVec[monsterID].m_monsterSprite.setPosition(monsterVec[monsterID].m_xPos * GRID_LEN, monsterVec[monsterID].m_yPos* GRID_LEN);
		addMonster(static_cast<Monsterid::ID>(monsterID), monsterVec[monsterID]);
	}
}

void MonsterManager::addMonster(Monsterid::ID monsterID, Monster& monsterEntity)
{
	std::unique_ptr<Monster> monsterPtr(new Monster());
	*monsterPtr = monsterEntity;
	monsterContainer.insert(std::make_pair(monsterID, std::move(monsterPtr)));
}

Monster& MonsterManager::findMonster(Monsterid::ID monsterID)
{
	auto iter = monsterContainer.find(monsterID);
	return *iter->second;
}

void MonsterManager::drawCurrentFloorMonster(sf::RenderWindow &l_window, const int currentFloor)
{
	for (int monsterID = Monsterid::Monster1; monsterID != Monsterid::Monster60; ++monsterID)
	{

		if (findMonster(static_cast<Monsterid::ID>(monsterID)).m_floor == currentFloor && !findMonster(static_cast<Monsterid::ID>(monsterID)).isDead)
		{
			findMonster(static_cast<Monsterid::ID>(monsterID)).draw(l_window);
		}
	}
}