#include "dialogue.h"

DialogBox::DialogBox(sf::RenderWindow& l_window, std::string &charName, std::vector<std::string> &dialogues, sf::Sprite &dialogBoxSp, sf::Font& engFont, sf::Font& chiFont) :
	mCharName(charName),
	mDialogues(dialogues),
	dialogFont(engFont),
	chDialogFont(chiFont),
	textColor(sf::Color::Black),
	textSize(30),
	isDisplayed(false),
	displayedTextLine(0),
	dialogBoxSprite(dialogBoxSp),
	useChFont(false),
	isTransacting(false),
	selectedID(ReturnGame),
	activeID(None)
{
	SellingButton HpBtn = { IncreaseHP , L"\u751f\u547d\u002b" , 100};
	SellingButton AtkBtn = { IncreaseAttack , L"\u653b\u64ca\u002b" , 10 };
	SellingButton DefBtn = { IncreaseDefense , L"\u9632\u79a6\u002b" , 10 };
	//SellingButton rtnBtn = { ReturnGame , L"\u9632\u79a6\u002b" , 10 };
	mButtonVec.push_back(HpBtn);
	mButtonVec.push_back(AtkBtn);
	mButtonVec.push_back(DefBtn);
}

void DialogBox::setDialog(std::string &charName, std::vector<std::string> &dialogues, bool isChString)
{
	useChFont = isChString;
	mCharName = charName;
	mDialogues = dialogues;
}

void DialogBox::setDialog(sf::String &charName, std::vector<sf::String> &dialogues, bool isChString, bool isMerchant, Player &l_buyer)
{
	buyer = &l_buyer;
	isTransacting = isMerchant;
	useChFont = isChString;
	mChCharName = charName;
	mChineseDialogues = dialogues;
}

void DialogBox::processEvent(sf::RenderWindow &l_window)
{
	sf::Event event;
	while (l_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case (sf::Keyboard::Up):
				if (isTransacting)
				{
					changeSelection(-1);
				}
				break;
			case (sf::Keyboard::Down):
				if (isTransacting)
				{
					changeSelection(1);
				}
				break;
			case (sf::Keyboard::Space):

				if (isTransacting)
				{
					Transaction(selectedID);
				}
				if (useChFont)
				{
					if (displayedTextLine == mChineseDialogues.size() - 1)
						isDisplayed = false;
					else
					{
						displayedTextLine++;
					}
				}
				else
				{
					if (displayedTextLine == mDialogues.size() - 1)
						isDisplayed = false;
					else
					{
						displayedTextLine++;
					}
				}
				

				break;
			default:
				break;
			}
			break;
		case sf::Event::Closed:
			l_window.close();
			break;
		default:
			break;
		}
	}
}

void DialogBox::changeSelection(int delta)
{
	int buttonID = static_cast<int>(selectedID) + delta;
	if (buttonID < 0)
	{
		buttonID += 4;
	}
	selectedID = static_cast<SellingOption>(buttonID % 4);
}

void DialogBox::setOption(const int increasedHP, const int increasedAtk, const int increasedDef, const int l_price)
{
	mButtonVec[0].value = increasedHP;
	mButtonVec[1].value = increasedAtk;
	mButtonVec[2].value = increasedDef;
	mPrice = l_price;
}

void DialogBox::Transaction(SellingOption selected)
{
	if (buyer->p_money >= mPrice)
	{
		buyer->p_money -= mPrice;
	}
	else
	{
		std::cout << "no money";
		return;
	}
		
	switch (selected)
	{
	case IncreaseHP:
		buyer->p_hp += mButtonVec[0].value;
		break;
	case IncreaseAttack:
		buyer->p_atk += mButtonVec[1].value;
		break;
	case IncreaseDefense:
		buyer->p_def += mButtonVec[2].value;
		break;
	}
}

void DialogBox::renderDialogBox(sf::RenderWindow& l_window, bool shallClear)
{
	if (shallClear)
	{
		l_window.clear();
	}
	l_window.draw(dialogBoxSprite);
	drawText(l_window);

	if (shallClear)
	{
		l_window.display();
	}
	
}

bool DialogBox::getState()
{
	return isDisplayed;
}

void DialogBox::setState(bool display)
{
	isDisplayed = display;
}

void DialogBox::drawText(sf::RenderWindow &l_window)
{
	float dialogPosY = window_height - dialogBoxSprite.getTexture()->getSize().y;
	if (!useChFont)
	{
		sf::Text nameTxt(mCharName + " : ", dialogFont, textSize);
		sf::Text dialogTxt(mDialogues.at(displayedTextLine), dialogFont, textSize);
		nameTxt.setPosition(1 * GRID_LEN, dialogPosY + 1 * GRID_LEN);
		nameTxt.setFillColor(textColor);
		dialogTxt.setPosition(1 * GRID_LEN, dialogPosY + 2 * GRID_LEN);
		dialogTxt.setFillColor(textColor);

		l_window.draw(nameTxt);
		l_window.draw(dialogTxt);
	}
	else
	{
		sf::Text nameTxt(mChCharName + " : ", chDialogFont, textSize);
		sf::Text dialogTxt(mChineseDialogues.at(displayedTextLine), chDialogFont, textSize);
		nameTxt.setPosition(1 * GRID_LEN, dialogPosY + 1 * GRID_LEN);
		nameTxt.setFillColor(textColor);
		dialogTxt.setPosition(1 * GRID_LEN, dialogPosY + 2 * GRID_LEN);
		dialogTxt.setFillColor(textColor);

		l_window.draw(nameTxt);
		l_window.draw(dialogTxt);
	}
	if (isTransacting)
	{
		drawButton(l_window);
	}
}

void DialogBox::drawButton(sf::RenderWindow &l_window)
{
	float dialogPosY = window_height - dialogBoxSprite.getTexture()->getSize().y;
	sf::Color selectedColor = { 150, 20, 20 };
	for (int btn = 0; btn < 3; ++btn)
	{
		if (selectedID == static_cast<SellingOption>(btn)) // is selected button
		{
			sf::Text buttonTxt(mButtonVec[btn].stringHead + std::to_wstring(mButtonVec[btn].value), chDialogFont, textSize);
			buttonTxt.setFillColor(selectedColor);
			buttonTxt.setPosition(1 * GRID_LEN, dialogPosY + 3 * GRID_LEN + btn * 60 - 5);
			l_window.draw(buttonTxt);
		}
		else
		{
			sf::Text buttonTxt(mButtonVec[btn].stringHead + std::to_wstring(mButtonVec[btn].value), chDialogFont, 20);
			buttonTxt.setFillColor(textColor);
			buttonTxt.setPosition(1 * GRID_LEN, dialogPosY + 3 * GRID_LEN + btn * 60);
			l_window.draw(buttonTxt);
		}
	}
}

void DialogBox::resetTextLine()
{
	displayedTextLine = 0;
}