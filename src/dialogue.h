#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "constVal.h"
#include "player.h"

enum SellingOption {
	None,
	IncreaseHP,
	IncreaseAttack,
	IncreaseDefense
	//ReturnGame
	
};

struct SellingButton {
	SellingOption buttonID;
	sf::String stringHead;
	int value;
};

class DialogBox
{
public : 
	DialogBox() { ; }
	DialogBox(sf::RenderWindow& l_window, std::string &charName ,std::vector<std::string> &dialogues, sf::Sprite &dialogBoxSp, sf::Font& engFont, sf::Font& chiFont); // take in a vector of strings
	void processEvent(sf::RenderWindow &l_window);
	void renderDialogBox(sf::RenderWindow& l_window, bool shallClear);
	bool getState();
	void setDialog(std::string &charName, std::vector<std::string> &dialogues, bool isChString);
	void setDialog(sf::String &charName, std::vector<sf::String> &dialogues, bool isChString, bool isMerchant, Player &l_buyer);
	void setOption(const int increasedHP, const int increasedAtk, const int increasedDef, const int l_price);
	
	void resetTextLine();
	void setState(bool display);
private:
	void Transaction(SellingOption selected);
	void changeSelection(int delta);
	void drawText(sf::RenderWindow &l_window);
	sf::Sprite dialogBoxSprite;
	sf::Font dialogFont;
	sf::Font chDialogFont;
	sf::Color textColor;
	// Flags
	bool useChFont;
	bool isTransacting;
	bool isDisplayed;

	// Button
	SellingOption selectedID;
	SellingOption activeID;
	int mPrice;
	std::vector<SellingButton> mButtonVec; // 0 = hp, 1 = atk, 2 = def
	void drawButton(sf::RenderWindow &l_window);
	Player* buyer;

	int textSize;
	int displayedTextLine;
	std::string mCharName;
	sf::String mChCharName;
	std::vector<std::string> mDialogues;
	std::vector<sf::String> mChineseDialogues;
	
};