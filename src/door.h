#pragma once
#include <SFML/Graphics.hpp>
#include "texture.h"
class door
{
public:
	door();
	door(int l_stage, int l_size, sf::Vector2u l_position, sf::Texture& l_texture);
	~door();
	void collide(sf::Vector2u l_position, int keyNum);

	void draw(sf::RenderTarget& target, int n_stage, int map[][]) const;


private:
	int n_size;
	int n_stage;
	bool** n_position;
	bool n_passable;
	sf::Sprite n_sprite;
};