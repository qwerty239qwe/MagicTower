#include "dialogue.h"

DialogBox::DialogBox(sf::RenderWindow& l_window, sf::Sprite &dialogBoxSp, sf::Font& engFont, sf::Font& chiFont) :
	mCharName(),
	mDialogues(),
	dialogFont(engFont),
	chDialogFont(chiFont),
	textColor(sf::Color::Black),
	textSize(30),
	isDisplayed(false),
	isCredits(false),
	displayedTextLine(0),
	dialogBoxSprite(dialogBoxSp),
	useChFont(false),
	isTransacting(false),
	isMonsterInfoBox(false),
	selectedID(None)
{
	SellingButton HpBtn = { IncreaseHP , L"\u751f\u547d\u002b" , 100};
	SellingButton AtkBtn = { IncreaseAttack , L"\u653b\u64ca\u002b" , 10 };
	SellingButton DefBtn = { IncreaseDefense , L"\u9632\u79a6\u002b" , 10 };

	mButtonVec.push_back(HpBtn);
	mButtonVec.push_back(AtkBtn);
	mButtonVec.push_back(DefBtn);
}

DialogBox::DialogBox(sf::RenderWindow& l_window, sf::Sprite &dialogBoxSp, sf::Font& engFont, sf::Font& chiFont, std::vector<sf::Sprite> &picVec) :
	mCharName(),
	mDialogues(),
	dialogFont(engFont),
	chDialogFont(chiFont),
	textColor(sf::Color::Black),
	textSize(30),
	displayedTextLine(0),
	dialogBoxSprite(dialogBoxSp),
	isDisplayed(false),
	isCredits(true),
	useChFont(false),
	isTransacting(false),
	isMonsterInfoBox(false),
	selectedID(None)
{
	mPicVec = picVec;
}

void DialogBox::setDialog(std::string &charName, std::vector<std::string> &dialogues, bool isChString)
{
	useChFont = isChString;
	mCharName = charName;
	mDialogues = dialogues;
}

void DialogBox::setDialog(std::vector<std::string> &dialogues, bool isChString)
{
	useChFont = isChString;
	mDialogues = dialogues;
}

void DialogBox::setDialog(std::vector<sf::String> &dialogues, bool isChString)
{
	useChFont = isChString;
	mChineseDialogues = dialogues;
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
				if (useChFont )
				{
					if (displayedTextLine == mChineseDialogues.size() - 1 || isCredits)
						isDisplayed = false;
					else
					{
						displayedTextLine++;
					}
				}
				else
				{
					if (displayedTextLine == mDialogues.size() - 1 || isCredits)
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
	if (buyer->p_money >= mPrice && selected != None)
	{
		buyer->p_money -= mPrice;
	}
	else
	{
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

	if (isCredits)
	{
		drawCredits(l_window);
	}
	else
	{
		drawText(l_window);
	}
	
	if (shallClear)
	{
		l_window.display();
	}
}

void DialogBox::renderDialogBox(sf::RenderWindow& l_window, MonsterManager &l_monsManager , std::vector<Monsterid::Type> typeVec, Player &l_player)
{
	l_window.draw(dialogBoxSprite);
	int monsType = 0;

	sf::Text hpHeader(std::string{ "HP" }, dialogFont, 25);
	sf::Text atkHeader(std::string{ "Atk" }, dialogFont, 25);
	sf::Text defHeader(std::string{ "Def" }, dialogFont, 25);
	sf::Text expHeader(std::string{ "EXP" }, dialogFont, 25);
	sf::Text mnyHeader(std::string{ "Money" }, dialogFont, 25);
	sf::Text exdHeader(std::string{ "Expected \nDamange" }, dialogFont, 25);

	std::vector<sf::Text> headerVec = { hpHeader, atkHeader, defHeader, expHeader, mnyHeader, exdHeader };
	for (int i = 0; i < headerVec.size(); ++i)
	{
		headerVec.at(i).setFillColor(sf::Color::Color(100, 75, 75));
		headerVec.at(i).setPosition(((2 + i) * 2 - 1) * GRID_LEN , GRID_LEN);
		l_window.draw(headerVec.at(i));
	}

	std::sort(typeVec.begin(), typeVec.end());
	for (int i = 0; i < typeVec.size(); ++i)
	{
		monsType++;
		sf::Sprite tempSp(l_monsManager.findMonsterTexture(typeVec.at(i)));
		tempSp.setPosition(1 * GRID_LEN, (monsType + 1) * (GRID_LEN));
		l_window.draw(tempSp);

		// draw values
		for (int j = 0; j < 5; ++j)
		{
			sf::Text valueTxt(std::to_string(l_monsManager.getMonsterValue(typeVec.at(i)).at(j)), dialogFont, 25);
			valueTxt.setFillColor(sf::Color::Color(50, 50, 50));
			valueTxt.setPosition(((2 + j) * 2 - 1) * GRID_LEN, (monsType + 1) * (GRID_LEN) + 20);
			l_window.draw(valueTxt);
		}
		int exd = l_monsManager.calculateExpectedDamage(l_player, typeVec.at(i));
		sf::Text exdValue;
		if (exd  == -1)
		{
			exdValue = sf::Text(std::string{"Infinity"}, dialogFont, 25);
		}
		else
		{
			exdValue = sf::Text(std::to_string(exd), dialogFont, 25);
		}
		
		exdValue.setFillColor(sf::Color::Color(50, 50, 50));
		exdValue.setPosition(((7) * 2 - 1) * GRID_LEN, (monsType + 1) * (GRID_LEN)+20);
		l_window.draw(exdValue);
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
		bool hasTitle = (mCharName != "") ? true : false;
		if (hasTitle)
		{
			sf::Text nameTxt(mCharName + " : ", dialogFont, textSize);
			nameTxt.setPosition(1 * GRID_LEN, dialogPosY + 1 * GRID_LEN);
			nameTxt.setFillColor(textColor);
			l_window.draw(nameTxt);
		}
		
		sf::Text dialogTxt(mDialogues.at(displayedTextLine), dialogFont, textSize);
		dialogTxt.setPosition(1 * GRID_LEN, dialogPosY + (1 + static_cast<int>(hasTitle)) * GRID_LEN);
		dialogTxt.setFillColor(textColor);
		l_window.draw(dialogTxt);
	}
	else
	{
		bool hasTitle = (mChCharName != "") ? true : false;
		if (hasTitle)
		{
			sf::Text nameTxt(mChCharName + " : ", chDialogFont, textSize);
			nameTxt.setPosition(1 * GRID_LEN, dialogPosY + 1 * GRID_LEN);
			nameTxt.setFillColor(textColor);
			l_window.draw(nameTxt);
		}
		
		sf::Text dialogTxt(mChineseDialogues.at(displayedTextLine), chDialogFont, textSize);
		dialogTxt.setPosition(1 * GRID_LEN, dialogPosY + (1 + static_cast<int>(hasTitle)) * GRID_LEN);
		dialogTxt.setFillColor(textColor);
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
		if (selectedID == static_cast<SellingOption>(btn+1)) // is selected button
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

void DialogBox::drawCredits(sf::RenderWindow &l_window)
{
	sf::Text creditsHead("CREDITS", dialogFont, textSize * 2);
	creditsHead.setFillColor(sf::Color(100, 50, 50));
	creditsHead.setPosition(l_window.getSize().x / 2 - creditsHead.getGlobalBounds().width / 2, 1 * GRID_LEN);
	l_window.draw(creditsHead);
	for (int p = 0; p < 4; p++)
	{
		mPicVec.at(p).setPosition((2 + 8 * ((p ) % 2)) * GRID_LEN, (3 + 4 * ((p ) / 2))* GRID_LEN);
		sf::Text creditsTxt(mDialogues.at(p), dialogFont, textSize*1.2);
		creditsTxt.setFillColor(textColor);
		creditsTxt.setPosition((2 + 8 * ((p ) % 2) + 1) * GRID_LEN, (3 + 4 * ((p ) / 2))* GRID_LEN);

		sf::Text creditsWorkTxt(mChineseDialogues.at(p), chDialogFont, textSize);
		creditsWorkTxt.setFillColor(textColor);
		creditsWorkTxt.setPosition((2 + 8 * ((p) % 2) + 1) * GRID_LEN, (3 + 4 * ((p) / 2) + 1)* GRID_LEN);

		l_window.draw(creditsTxt);
		l_window.draw(creditsWorkTxt);
		l_window.draw(mPicVec.at(p));
	}
}

void DialogBox::resetTextLine()
{
	displayedTextLine = 0;
}