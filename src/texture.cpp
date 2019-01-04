#include "texture.h"

TextureManager::TextureManager()
{
	load(Textures::Teacher, "TeacherAni.png");
	load(Textures::TeacherStand, "heyTeacher.png");
	load(Textures::BackGround, "testBG.jpg");
	load(Textures::DialogBig, "dialog_B.png");
	load(Textures::DialogMedium, "dialog_M.png");
	load(Textures::DialogSmall, "dialog_S.png");
	load(Textures::Map, "map.png");
	load(Textures::Wall, "wall.png");
	load(Textures::UpStair, "upStair.png");
	load(Textures::DownStair, "downStair.png");
	load(Textures::RedKey, "redKey.png");
	load(Textures::YellowKey, "yellowKey.png");
	load(Textures::BlueKey, "blueKey.png");
	load(Textures::RedDoor, "redDoor.png");
	load(Textures::YellowDoor, "yellowDoor.png");
	load(Textures::BlueDoor, "blueDoor.png");
	load(Textures::IronDoor, "ironDoor.png");
	load(Textures::Slime, "slime.png");
	load(Textures::Slime2, "Blueslime.png");
}

void TextureManager::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());		// create a texture pointer
	texture->loadFromFile(SPRITE_PATH + filename);					// load a texture from local file
	
	mTextureStorage.insert(std::make_pair(id, std::move(texture)));	// append the texture to the textureStorage
}

sf::Texture& TextureManager::get(Textures::ID id)
{
	auto found = mTextureStorage.find(id);							// use ID to find texture
	return *found->second;											// return texture pointer
}

const sf::Texture& TextureManager::get(Textures::ID id) const
{
	auto found = mTextureStorage.find(id);							// use ID to find texture
	return *found->second;
}
