#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "constVal.h"



namespace Textures 
{ 
	enum ID { BackGround, DialogBig, DialogMedium, DialogSmall, Map, 
		Teacher, TeacherStand, NPC, NPC2,
		Wall, UpStair, DownStair, RedDoor, BlueDoor, YellowDoor, IronDoor,
		RedKey, BlueKey, YellowKey, RedPosion, BluePosion,
		Slime, Slime2};
}

class TextureManager
{
public:
	TextureManager();
	void load(Textures::ID id, const std::string& filename);				// load textures from files
	sf::Texture& get(Textures::ID id);										// get texture pointer by ID
	const sf::Texture& get(Textures::ID id) const;							// caller cannot change the texture in this function
private:
	std::map <Textures::ID, std::unique_ptr<sf::Texture>> mTextureStorage;	// mapping id to textures, this is the place textures stored
																			// the smart pointer help us to manage the construction and destruction of pointer
};

