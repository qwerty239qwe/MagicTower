#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"

class MainGame
{
public :
	MainGame(TextureManager &l_textures);
	void processEvents(sf::RenderWindow &l_window);
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow &l_window);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:

	TextureManager *mTextures;
	sf::Sprite mPlayer;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	float PlayerSpeed = 100.f;

};