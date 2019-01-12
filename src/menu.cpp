#include "menu.h"

Menu::Menu(sf::Sprite &backgroundImg, sf::Font buttonFont, sf::Color buttonColor, sf::Color selectedColor, BGMmanager& bgm):
	backgroundImg(backgroundImg),
	buttonFont(buttonFont),
	buttonFontSize(60),
	buttonColor(buttonColor),
	selectedColor(selectedColor),
	selectedID(0),
	activeID(-1)
{
	bgm.play(BGM::menuBGM);
	Button btn1{ GameStart, "Game Start"};
	Button btn2{ Load, "Information"};
	Button btn3{ Info, "Credits"};
	buttonVec.push_back(btn1);
	buttonVec.push_back(btn2);
	buttonVec.push_back(btn3);
}

int Menu::getActiveID()
{
	return activeID;
}

void Menu::changeSelection(int dID)
{
	selectedID += dID;
	if (selectedID < 0)
	{
		selectedID += 3;
	}
	selectedID = (selectedID) % 3;
}

void Menu::processEvent(sf::RenderWindow &l_window)
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
				changeSelection(-1);
				break;
			case (sf::Keyboard::Down):
				changeSelection(1);
				break;
			case (sf::Keyboard::Space):
				activeID = selectedID;
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

void Menu::drawButton(int &buttonID, sf::RenderWindow &l_window)
{
	sf::Text btnText(buttonVec[buttonID].buttonText, buttonFont, buttonFontSize);
	if (selectedID == buttonID)
	{
		btnText.setCharacterSize(buttonFontSize * 1.2);
		btnText.setPosition(l_window.getSize().x / 2 - btnText.getGlobalBounds().width / 2, 440 + buttonID * 110);
		btnText.setFillColor(selectedColor);
	}
	else
	{
		btnText.setFillColor(buttonColor);
		btnText.setPosition(l_window.getSize().x / 2 - btnText.getGlobalBounds().width / 2, 440 + buttonID * 110);
	}
	l_window.draw(btnText);
}

void Menu::render(sf::RenderWindow &l_window)
{
	l_window.clear();
	l_window.draw(backgroundImg);
	for (int i = 0; i < 3; i++)
	{
		drawButton(i, l_window);
	}
	l_window.display();
}

void Menu::resetActiveID()
{
	activeID = -1;
}