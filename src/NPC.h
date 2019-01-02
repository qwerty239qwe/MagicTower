#pragma once 
#include <SFML/Graphics.hpp>
#include <string>
#include "texture.h"
#include <vector>
#include "player.h"



class NPC
{	
	
public:
	NPC() { ; }
	NPC(Position l_positon,int l_what, int l_type, int id);
	~NPC() { ; }
	sf::Sprite n_npcSprite;
	void onCollision(Player& p_player);//碰撞  跑出對話
	void draw(sf::RenderTarget& target) const;
private:
	int what ;  //0 none  1 npc  2 monster  3  others
	int type;  //1 只有對話  2商人
	std::string n_dialogue;
	Position n_position;

	std::vector<sf::String> n_sentences;


};

