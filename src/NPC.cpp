#include "NPC.h"
 
NPC::NPC(int l_floor, int l_xPos, int l_yPos, int l_type, int l_isDead ,sf::String l_name, std::vector<sf::String> l_dialogue):
	n_xPos(l_xPos), n_yPos(l_yPos), type(l_type), isDead(!static_cast<bool>(l_isDead)), n_floor(l_floor), n_dialogue(l_dialogue), n_name(l_name)
{	
	n_npcSprite.setPosition(n_xPos*GRID_LEN, n_yPos*GRID_LEN);
}

void NPC::draw(sf::RenderWindow &l_window) const
{
	l_window.draw(n_npcSprite);
}

void NPC::onCollision(Player& n_player, DialogBox &n_dialogBox)
{
	if (this->type == 1)
	{
		//印出對話框
		n_dialogBox.setDialog(n_name, n_dialogue, true, false, n_player);
		n_dialogBox.setState(true);
		n_dialogBox.resetTextLine();
		n_player.p_exp += 100;
		n_player.checkLevelUp();
		
		isDead = true;
	}
	if (this->type == 2)
	{
		//印出對話框;
		n_dialogBox.setDialog(n_name, n_dialogue, true, true, n_player);
		n_dialogBox.setOption(transactionInfo[0], transactionInfo[1], transactionInfo[2], transactionInfo[3]);
		n_dialogBox.setState(true);
		n_dialogBox.resetTextLine();
	}
}

NPCmanager::NPCmanager(std::vector<std::vector<int>> &data, TextureManager &l_textures)
{
	npcSentence sentContainer;
	std::vector<NPC> npcVec(countNPC);
	sf::String NPCNAME = "NPC";
	for (int npcID = NPCid::NPC1; npcID != NPCid::NPC12; ++npcID)
	{
		npcVec[npcID] = NPC(data[npcID][2], data[npcID][0], data[npcID][1], data[npcID][4], data[npcID][3],
			NPCNAME, (sentContainer.getSentence(static_cast<NPCid::ID>(npcID))));
		std::vector<int> l_transaction(4);
		switch (npcID)
		{
		case NPCid::NPC6:
			l_transaction = { 100, 10, 10, 100 };
			npcVec[npcID].transactionInfo = l_transaction;	// vector should deep copy here
			break;
		case NPCid::NPC8:
			l_transaction = { 250, 25, 25, 200 };
			npcVec[npcID].transactionInfo = l_transaction; // vector should deep copy here
			break;
		case NPCid::NPC9:
			l_transaction = { 450, 45, 45, 300 };
			npcVec[npcID].transactionInfo = l_transaction; // vector should deep copy here
			break;
		default:
			break;
		}
		npcVec[npcID].n_npcSprite.setTexture(l_textures.get(Textures::NPC));
		npcVec[npcID].n_npcSprite.setPosition(npcVec[npcID].n_xPos * GRID_LEN, npcVec[npcID].n_yPos* GRID_LEN);
		addNPC(static_cast<NPCid::ID>(npcID), npcVec[npcID]);
	}
}

void NPCmanager::addNPC(NPCid::ID npcID, NPC& npcEntity)
{
	std::unique_ptr<NPC> npcPtr(new NPC());
	*npcPtr = npcEntity;
	NPCcontainer.insert(std::make_pair(npcID, std::move(npcPtr)));
}

NPC& NPCmanager::findNPC(NPCid::ID npcID)
{
	auto iter = NPCcontainer.find(npcID);
	return *iter->second;
}

void NPCmanager::drawCurrentFloorNPC(sf::RenderWindow &l_window, const int currentFloor)
{
	for (int npcID = NPCid::NPC1; npcID != NPCid::NPC12; ++npcID)
	{
		
		if (findNPC(static_cast<NPCid::ID>(npcID)).n_floor == currentFloor && !findNPC(static_cast<NPCid::ID>(npcID)).isDead)
		{
			findNPC(static_cast<NPCid::ID>(npcID)).draw(l_window);
		}
	}
}