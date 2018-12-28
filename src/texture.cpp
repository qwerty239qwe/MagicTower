#include "texture.h"

void TextureManager::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());		// create a texture pointer
	texture->loadFromFile(filename);								// load a texture from local file
	
	mTextureStorage.insert(std::make_pair(id, std::move(texture)));	// append the texture to the textureStorage
}

sf::Texture& TextureManager::get(Textures::ID id)
{
	auto found = mTextureStorage.find(id);							// use ID to find texture
	return *found->second;											// return texture pointer
}
