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
	if (type = 0)  //���
	{
		return;
	}
	if (type = 1)  //����
	{
		if (l_player.yellowKeys > 0)
		{
			l_player.yellowKeys--;
			what = 0;
		}
	}
	if (type = 2)  //����
	{
		if (l_player.redKeys > 0)
		{
			l_player.redKeys--;
			what = 0;
		}
	}
	if (type = 3)  //�Ū�
	{
		if (l_player.blueKeys > 0)
		{
			l_player.blueKeys--;
			what = 0;
		}
	}
	if (type = 4)  //���_��
	{
		l_player.yellowKeys++;
		what = 0;
	}
	if (type = 5)  //���_��
	{
		l_player.redKeys++;
		what = 0;
	}
	if (type = 6)  //���_��
	{
		l_player.blueKeys++;
		what = 0;
	}
	if (type = 7)  //����U
	{
		level++;
	}
	if (type = 8)  //����W
	{
		level--;
	}
	if (type = 9)  //red�Ĥ�
	{
		l_player.hp+=150;
		what = 0;
	}
	if (type = 10)  //blue�Ĥ�
	{
		l_player.hp += 300;
		what = 0;
	}
	if (type = 11)  //�K��
	{
		what = 0;
	}
	if (type = 12)  //�C
	{
		l_player.atk+= 5;
		what = 0;
	}
	if (type = 13)  //�޵P
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