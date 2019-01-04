#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "sound.h"

enum ButtonOptions {
	GameStart,
	Load,
	Info
};

struct Button
{
	ButtonOptions buttonID;		// Store button ID
	std::string buttonText;		// Store text of button
};

class Menu
{
public:
	Menu(sf::Sprite &backgroundImg, sf::Font buttonFont, sf::Color buttonColor, sf::Color selectedColor, BGMmanager& bgm);
	int getActiveID();
	void resetActiveID();
	void processEvent(sf::RenderWindow &l_window);
	void render(sf::RenderWindow &l_window);

private:
	sf::Sprite backgroundImg;
	sf::Font buttonFont;
	sf::Color buttonColor;
	sf::Color selectedColor;
	std::vector<Button> buttonVec;		// store buttons
	int selectedID;
	int activeID;
	int buttonFontSize;					// in pixels
	void drawButton(int &buttonID, sf::RenderWindow &l_window);
	void changeSelection(int dID);
};