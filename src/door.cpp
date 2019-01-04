#include "door.h"
door::door(int d_x, int d_y, int d_level, int d_what, int d_type)
{
	sf::Sprite n_sprite;
	int level = d_level;
	int x = d_x;
	int y = d_y;
	int what = d_what;
	int type = d_type;

	
}
void door::oncollision(Player& l_player)
{
	if (type = 0)  //Àð¾À
	{
		return;
	}
	if (type = 1)  //¶Àªù
	{
		if (l_player.yellowKeys > 0)
		{
			l_player.yellowKeys--;
			what = 0;
		}
	}
	if (type = 2)  //¬õªù
	{
		if (l_player.redKeys > 0)
		{
			l_player.redKeys--;
			what = 0;
		}
	}
	if (type = 3)  //ÂÅªù
	{
		if (l_player.blueKeys > 0)
		{
			l_player.blueKeys--;
			what = 0;
		}
	}
	if (type = 4)  //¶ÀÆ_°Í
	{
		l_player.yellowKeys++;
		what = 0;
	}
	if (type = 5)  //¬õÆ_°Í
	{
		l_player.redKeys++;
		what = 0;
	}
	if (type = 6)  //ÂÅÆ_°Í
	{
		l_player.blueKeys++;
		what = 0;
	}
	if (type = 7)  //¶¥±è¤U
	{
		level++;
	}
	if (type = 8)  //¶¥±è¤W
	{
		level--;
	}
	if (type = 9)  //redÃÄ¤ô
	{
		l_player.hp+=150;
		what = 0;
	}
	if (type = 10)  //blueÃÄ¤ô
	{
		l_player.hp += 300;
		what = 0;
	}
	if (type = 11)  //ÅKªù
	{
		what = 0;
	}
	if (type = 12)  //¼C
	{
		l_player.atk+= 5;
		what = 0;
	}
	if (type = 13)  //¬ÞµP
	{
		l_player.def+=5;
		what = 0;
	}
}

door::~door()
{

}

void door::draw(sf::RenderTarget & target, int n_stage,int map[][11]) const
{
	window.draw(n_sprite);
}