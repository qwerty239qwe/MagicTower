#include "tile.h"

Tile::Tile(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead):
	t_floor(l_floor), t_xPos(l_xPos), t_yPos(l_yPos), type(l_type), isDead(!static_cast<bool>(l_isDead))
{
	
}

void Tile::onCollision(Player &l_player, int &floor)
{
	switch (type)
	{
	case 0: // Wall
		break;

	case 1:
		if (l_player.p_yellowKeys > 0)
		{
			l_player.p_yellowKeys--;
			isDead = true;
		}
		break;
	case 2:
		if (l_player.p_redKeys > 0)
		{
			l_player.p_redKeys--;
			isDead = true;
		}
		break;
	case 3:
		if (l_player.p_blueKeys > 0)
		{
			l_player.p_blueKeys--;
			isDead = true;
		}
		break;
	case 4:
		l_player.p_yellowKeys++;
		isDead = true;
		break;
	case 5:
		l_player.p_redKeys++;
		isDead = true;
		break;
	case 6:
		l_player.p_blueKeys++;
		isDead = true;
		break;
	case 7:		// Downstair
		floor--;
		break;
	case 8:		// UpStair
		floor++;
		break;
	case 9:		// red posion
		l_player.p_hp += 100;
		isDead = true;
		break;
	case 10:	// blue posion
		l_player.p_hp += 500;
		isDead = true;
		break;
	case 11:	// IronDoor
		isDead = true;
		break;
	case 12:	// sword
		l_player.p_atk += 15;
		isDead = true;
		break;
	case 13:	// shield
		l_player.p_def += 15;
		isDead = true;
		break;
	}
}

void Tile::draw(sf::RenderWindow& l_window)const
{
	l_window.draw(t_tileSprite);
}


TileManager::TileManager(std::vector<std::vector<int>> &data, TextureManager &l_textures)
{
	std::vector<Tile> tileVec(countTile);

	for (int tileID = TileID::Wall1; tileID != TileID::Downstair10; ++tileID)
	{
		tileVec[tileID] = Tile(data[tileID][2], data[tileID][0], data[tileID][1], data[tileID][4], data[tileID][3]);
		switch (data[tileID][4])
		{
		case 0:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::Wall));
			break;
		case 1:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::YellowDoor));
			break;
		case 2:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::RedDoor));
			break;
		case 3:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::BlueDoor));
			break;
		case 4:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::YellowKey));
			break;
		case 5:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::RedKey));
			break;
		case 6:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::BlueKey));
			break;
		case 7:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::DownStair));
			break;
		case 8:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::UpStair));
			break;
		case 9:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::RedPosion));
			break;
		case 10:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::BluePosion));
			break;
		case 11:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::IronDoor));
			break;
		case 12:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::Sword));
			break;
		case 13:
			tileVec[tileID].t_tileSprite.setTexture(l_textures.get(Textures::Shield));
			break;
		default:
			break;
		}
		
		//npcVec[npcID].n_npcSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(40, 40)));
		tileVec[tileID].t_tileSprite.setPosition(tileVec[tileID].t_xPos * GRID_LEN, tileVec[tileID].t_yPos* GRID_LEN);
		addTile(static_cast<TileID::ID>(tileID), tileVec[tileID]);
	}
}


void TileManager::addTile(TileID::ID tileID, Tile& tileEntity)
{
	std::unique_ptr<Tile> tilePtr(new Tile());
	*tilePtr = tileEntity;
	tileContainer.insert(std::make_pair(tileID, std::move(tilePtr)));
}

Tile& TileManager::findTile(TileID::ID tileID)
{
	auto iter = tileContainer.find(tileID);
	return *iter->second;
}

void TileManager::drawCurrentFloorTile(sf::RenderWindow &l_window, const int currentFloor)
{
	for (int tileID = TileID::Wall1; tileID != TileID::Downstair10; ++tileID)
	{
		if (findTile(static_cast<TileID::ID>(tileID)).t_floor == currentFloor && !findTile(static_cast<TileID::ID>(tileID)).isDead)
		{
			findTile(static_cast<TileID::ID>(tileID)).draw(l_window);
		}
	}
}