#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureManager.h"
#include <vector>

using std::vector;
//shoudl my board class contain static variables
//should I reveal the mines first before dealing with flags
class Board
{
	int numCol; //number of columns on the board
	int numRow; //number of rows on the board

	//sf::Sprite counterDisplay;
	//probably should have a function that helps display the digit counter based on flagcounter value (maybe passes in a window and draws).
	
	//you should probably have a counter for number of tiles  revealed (possibly when (col * row - mine count) == numOftiles revealed, the game ends in victory and we change to cool face
	//should my board have a 

public:
	//void DisplayCounter(sf::RenderWindow& window);
	int flagCounter;
	int mineCount;
	int revealCounter;
	bool isLossed;
	bool won;
	bool debuggerOn;
	vector<vector<Tile>> tiles; //return by reference
	Board(int& col, int& row, int& mine);
	void Create();
	void clear(int mine);

	void testBoard(string filename);

	//void DebuggerOn();

};

