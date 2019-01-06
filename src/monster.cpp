#include "monster.h"

Monster::Monster(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead, int l_hp, int l_atk, int l_def, int l_exp, int l_money):
	m_floor(l_floor), type(l_type), 
	m_xPos(l_xPos), m_yPos(l_yPos), isDead(!static_cast<bool>(l_isDead)),
	m_hp(l_hp), m_atk(l_atk), m_def(l_def), m_exp(l_exp), m_money(l_money)
{
	
}

void Monster::onCollision(Player& l_player)
{
	if (l_player.p_atk - m_def <= 0 && m_atk - l_player.p_def <= 0)
	{
		return;		// no winner
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
				return;
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
	addMonsterType(Monsterid::Slime, l_textures.get(Textures::Slime));
	addMonsterType(Monsterid::Slime2, l_textures.get(Textures::Slime2));
	addMonsterType(Monsterid::Skeleton, l_textures.get(Textures::Skeleton));
	addMonsterType(Monsterid::SkeletonWarrior, l_textures.get(Textures::SkeletonWarrior));
	addMonsterType(Monsterid::GitCat, l_textures.get(Textures::GitCat));
	addMonsterType(Monsterid::Pikachu, l_textures.get(Textures::Pikachu));

	monsterValue.insert(std::make_pair(Monsterid::Slime, std::vector<int>{36, 12, 4, 1, 5}));
	monsterValue.insert(std::make_pair(Monsterid::Slime2, std::vector<int>{10, 15, 8, 1, 4}));
	monsterValue.insert(std::make_pair(Monsterid::Skeleton, std::vector<int>{42, 25, 16, 2, 4}));
	monsterValue.insert(std::make_pair(Monsterid::SkeletonWarrior, std::vector<int>{32, 40, 20, 2, 15}));
	monsterValue.insert(std::make_pair(Monsterid::GitCat, std::vector<int>{105, 85, 40, 8, 80}));
	monsterValue.insert(std::make_pair(Monsterid::Pikachu, std::vector<int>{220, 120, 60, 8, 80}));

	for (int monsterID = 0; monsterID < countMonster; ++monsterID)
	{
		monsterVec[monsterID] = Monster(data[monsterID][2], data[monsterID][0], data[monsterID][1], data[monsterID][4], data[monsterID][3],
			monsterValue.find(static_cast<Monsterid::Type>(data[monsterID][4]))->second.at(0), 
			monsterValue.find(static_cast<Monsterid::Type>(data[monsterID][4]))->second.at(1),
			monsterValue.find(static_cast<Monsterid::Type>(data[monsterID][4]))->second.at(2),
			monsterValue.find(static_cast<Monsterid::Type>(data[monsterID][4]))->second.at(3),
			monsterValue.find(static_cast<Monsterid::Type>(data[monsterID][4]))->second.at(4));
		monsterVec[monsterID].m_monsterSprite.setTexture(findMonsterTexture(static_cast<Monsterid::Type>(data[monsterID][4])));
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

void MonsterManager::addMonsterType(Monsterid::Type monsterType, sf::Texture& monsterTexture)
{
	std::unique_ptr<sf::Texture> monsterTexturePtr(new sf::Texture());
	*monsterTexturePtr = monsterTexture;
	monsterTextures.insert(std::make_pair(monsterType, std::move(monsterTexturePtr)));
}

sf::Texture& MonsterManager::findMonsterTexture(Monsterid::Type monsterType) // find monster textures by type name
{
	auto iter = monsterTextures.find(monsterType);
	return *iter->second;
}

void MonsterManager::drawCurrentFloorMonster(sf::RenderWindow &l_window, const int currentFloor)
{
	for (int monsterID = Monsterid::Monster1; monsterID < countMonster; ++monsterID)
	{

		if (findMonster(static_cast<Monsterid::ID>(monsterID)).m_floor == currentFloor && !findMonster(static_cast<Monsterid::ID>(monsterID)).isDead)
		{
			findMonster(static_cast<Monsterid::ID>(monsterID)).draw(l_window);
		}
	}
}

std::vector<Monsterid::Type> MonsterManager::getMonsterType(const int currentFloor)
{
	std::vector<Monsterid::Type> monsterTypeVec;
	for (int monsterID = Monsterid::Monster1; monsterID < countMonster; ++monsterID)
	{

		if (findMonster(static_cast<Monsterid::ID>(monsterID)).m_floor == currentFloor && !findMonster(static_cast<Monsterid::ID>(monsterID)).isDead)
		{
			if (!monsterTypeVec.empty())
			{
				for (auto iter = monsterTypeVec.begin();
					*iter != static_cast<Monsterid::Type>(findMonster(static_cast<Monsterid::ID>(monsterID)).type) &&
					iter != monsterTypeVec.end();
					++iter)
				{
					if (iter == monsterTypeVec.end() - 1)
					{
						monsterTypeVec.push_back(static_cast<Monsterid::Type>(findMonster(static_cast<Monsterid::ID>(monsterID)).type));
					}
				}
			}
			else
			{
				monsterTypeVec.push_back(static_cast<Monsterid::Type>(findMonster(static_cast<Monsterid::ID>(monsterID)).type));
			}
			
		}
	}
	return monsterTypeVec;
}

std::vector<int> MonsterManager::getMonsterValue(Monsterid::Type monsterType)
{
	return monsterValue.find(monsterType)->second;
}

int MonsterManager::calculateExpectedDamage(Player &l_player, Monsterid::Type monsterType)
{
	int virtualMonsterHp = getMonsterValue(monsterType).at(0),
		virtualMonsterAtk = getMonsterValue(monsterType).at(1),
		virtualMonsterDef = getMonsterValue(monsterType).at(2);
	int ExpectedDamage = 0;
	if (l_player.p_atk - virtualMonsterDef <= 0 && virtualMonsterAtk - l_player.p_def <= 0)
	{
		return -1;		// no winner
	}

	if (l_player.p_atk - virtualMonsterDef <= 0 && virtualMonsterAtk - l_player.p_def > 0)
	{
		return 999999;	// player will die
	}

	while (virtualMonsterHp > 0)
	{
		if (l_player.p_atk - virtualMonsterDef > 0)
			virtualMonsterHp -= (l_player.p_atk - virtualMonsterDef);
		if (virtualMonsterHp > 0 && virtualMonsterAtk - l_player.p_def > 0)
		{
			ExpectedDamage += (virtualMonsterAtk - l_player.p_def);
		}
	}
	return ExpectedDamage;
}