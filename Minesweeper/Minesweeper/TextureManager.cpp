#include "TextureManager.h"

// "redeclare" the variable, so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
	//fileName == space 
	//path == images/space.png
}


sf::Texture& TextureManager::GetTexture(string textureName) {

	//if the texture DOESN'T exist...
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear(); //get rid of all the stored objects
}