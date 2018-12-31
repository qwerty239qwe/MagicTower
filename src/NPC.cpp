#include "NPC.h"
 
NPC::NPC( Position l_position, int l_what, int l_type, std::string l_dialogue) 
{	
	n_position.x = l_position.x;
	n_position.y = l_position.y;
	n_position.z = l_position.z;
	what = l_what;
	type = l_type;
	n_dialogue = n_dialogue;
}

void NPC::draw(sf::RenderTarget & target) const
{
	target.draw(n_npcSprite);
}

void NPC::onCollision(Player% n_player)

{
	if (this->type == 1)
	{
		//印出對話框
		what = 0;
	}
	if (this->type == 2)
	{
		;//印出對話框;
	}

		
}