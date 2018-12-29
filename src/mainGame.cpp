#include "mainGame.h"

MainGame::MainGame(TextureManager &l_textures) :
	PlayerSpeed(1000.f)
{
	mTextures = &l_textures;
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setTexture(mTextures->get(Textures::Teacher));
}

void MainGame::processEvents(sf::RenderWindow& l_window)
{
	sf::Event event;
	while (l_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			l_window.close();
		else if (event.type == sf::Event::KeyPressed)
			handlePlayerInput(event.key.code, true);
		else if (event.type == sf::Event::KeyReleased)
			handlePlayerInput(event.key.code, false);
	}
}

void MainGame::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	mPlayer.move(movement * deltaTime.asSeconds());
}

void MainGame::render(sf::RenderWindow &l_window)
{
	l_window.clear();
	l_window.draw(mPlayer);
	l_window.display();
}

void MainGame::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
}