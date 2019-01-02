#include "door.h"
door::door(int l_stage, int l_size, sf::Vector2u l_position, sf::Texture& l_texture)
{
	n_size = l_size;
	n_stage = l_stage;
	n_sprite.setTexture(l_texture);
	n_passable = 0;
}


door::~door()
{

}
void door::collide(sf::Vector2u l_position, int keyNum)
{
	if (i == )
	{
		if (keyNum >= 1)
		{
			n_passable[i] = 1;
			keyNum = keyNum - 1;
		}
	}

}

void door::draw(sf::RenderTarget & target, int n_stage,int map[][]) const
{
	int j =  n_stage;
	for (int i = 0; i < 11; i++)
	{
		for (int i = 0; i < 11; i++)
		{
			if (number[j][i] == 1)
			{
				n_sprite.setTexture->setPosition(i * 88, j * 88);
				target.draw(n_sprite);
			}
		}
	}
}