#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class TextureManager
{
	// static == one and only one of these in memory, ever
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName); //LoadTexture("space");

public:
	//you need to put static on the functions since we used static on the map
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); // Call this once, at the end of main()
};