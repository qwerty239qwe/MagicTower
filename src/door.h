#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "player.h"
class door
{
public:
	door();
	door(int d_x, int d_y, int d_level, int d_what, int d_type);
	~door();
	sf::Sprite n_sprite;
	void oncollision(Player& l_player);

private:
	int level;
	int x;
	int y;
	int what;
	int type;	
};