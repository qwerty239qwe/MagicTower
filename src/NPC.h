#pragma once 
#include <SFML/Graphics.hpp>
#include <string>
#include "texture.h"
#include "Player.h"
#include "initialize.h"
#include "dialogue.h"



class NPC
{	
	friend class MainGame;
	friend class NPCmanager;
public:
	NPC() { ; }
	NPC(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead, sf::String l_name, std::vector<sf::String> l_dialogue);
	~NPC() { ; }
	void onCollision(Player& n_player, DialogBox &n_dialogBox);//碰撞  跑出對話
	void draw(sf::RenderWindow &l_window) const;
private:
	//int what ;  //0 none,  1 npc,  2 monster,  3 others
	sf::Sprite n_npcSprite;
	bool isDead;
	int type;  // 1 只有對話,  2 商人
	std::vector<sf::String> n_dialogue;
	sf::String n_name;
	int n_floor;
	int n_xPos;
	int n_yPos;
	std::vector<int> transactionInfo;
};

class NPCmanager
{
public :
	NPCmanager() { ; }
	NPCmanager(std::vector<std::vector<int>> &data, TextureManager &l_textures); // initialize every NPC here
	void addNPC(NPCid::ID npcID, NPC& npcEntity);
	NPC& findNPC(NPCid::ID npcID);

	void drawCurrentFloorNPC(sf::RenderWindow &l_window, const int currentFloor);
private:
	std::map <NPCid::ID, std::unique_ptr<NPC>> NPCcontainer;
};