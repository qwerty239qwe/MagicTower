#pragma once 
#include <SFML/Graphics.hpp>
#include <string>
#include "texture.h"
#include "Player.h"
struct Position 
{
	int x; int y; int z;
};


class NPC
{	
	
public:
	NPC() { ; }
	NPC(Position l_positon,int l_what, int l_type, std::string l_dialogue);
	~NPC() { ; }
	sf::Sprite n_npcSprite;
	void onCollision(Player% n_player);//�I��  �]�X���
	void draw(sf::RenderTarget& target) const;
private:
	int what ;  //0 none  1 npc  2 monster  3  others
	int type;  //1 �u�����  2�ӤH
	std::string n_dialogue;
	Position n_position;
	

};

