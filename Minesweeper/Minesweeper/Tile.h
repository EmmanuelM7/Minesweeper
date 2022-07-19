#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Tile
{
	sf::Sprite hiddenTile;
	int width;
	int height;
	//bool isFlagged;
	sf::Sprite flaggedImage;
	sf::Sprite mine;
	sf::Sprite tileRevealed;
	

	//should this have a vector<Tile*> adjacentTiles because each tile may have a number of adjacent tiles

public:
	void DrawFlag(sf::RenderWindow& window);
	vector<Tile*> adjacentTiles;
	bool isMine;
	bool isFlagged;
	bool isRevealed;
	bool isDebugged;

	Tile(string filename);
	void Display(sf::RenderWindow& window);

	int getHeight();
	int getWidth();

	void setPos(sf::Vector2f position);
	void setPos(float x, float y);
	sf::Vector2f getPos();

	//void DebugTile(sf::RenderWindow& window);

	sf::FloatRect GetSpriteRect();


	void DrawMine(sf::RenderWindow& window);
};

