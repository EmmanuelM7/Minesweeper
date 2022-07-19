#include "Tile.h"
#include <string>
#include "TextureManager.h"
#include <vector>

using std::string;

Tile::Tile(string filename) {
	hiddenTile.setTexture(TextureManager::GetTexture(filename));
	flaggedImage.setTexture(TextureManager::GetTexture("flag"));
	mine.setTexture(TextureManager::GetTexture("mine"));
	tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	width = hiddenTile.getGlobalBounds().width;
	height = hiddenTile.getGlobalBounds().height;
	isFlagged = false;
	isMine = false;
	isRevealed = false;
	isDebugged = false;
	
}

void Tile::Display(sf::RenderWindow& window) {

	//window.draw(hiddenTile);
	/*if (isFlagged) {
		window.draw(flaggedImage);
	}*/
	//window.draw(hiddenTile);

	window.draw(hiddenTile);



	if (isRevealed && isMine) {
		window.draw(mine);
	}
	else if (!isRevealed && !isMine) {
		window.draw(hiddenTile);
	}
	else if (isRevealed && !isMine) {
		window.draw(tileRevealed);
	}



	if (isFlagged) {
		window.draw(flaggedImage);
	}

	if (isDebugged && isMine) {
		window.draw(mine);
	}

	//if (isRevealed && isMine)
	//{
	//	window.draw(mine);
	//}

	//if (isMine) {
	//	window.draw(mine);
	//}


	/*if (!isDebugged && isMine && isRevealed) {
		window.draw(mine);
	}*/

	/*else if (!isDebugged && isMine) {
		window.draw(mine);
	}*/

	//if (isFlagged) {
	//	window.draw(flaggedImage);
	//	isMine = false;
	//}
	//else {
	//	window.draw(hiddenTile);
	//}
	//
	//if (isRevealed && isMine && !isFlagged) {
	//	window.draw(mine);
	//}

	
	/*if (!isFlagged) {
		window.draw(hiddenTile);
	}*/
	




	//if (isFlagged) {
	//	window.draw(hiddenTile);
	//	window.draw(flaggedImage);
	////	//window.draw(mine);
	////	//window.draw(mine);

	//}
	//else {
	//	window.draw(hiddenTile);
	//}
	//

}

int Tile::getHeight() {
	return height;
}

int Tile::getWidth() {
	return width;
}

void Tile::setPos(sf::Vector2f position) {
	hiddenTile.setPosition(position);
	mine.setPosition(position);
	flaggedImage.setPosition(position);
	tileRevealed.setPosition(position);
}

void Tile::setPos(float x, float y) {
	hiddenTile.setPosition(x, y);
	mine.setPosition(x, y);
	flaggedImage.setPosition(x,y);
	tileRevealed.setPosition(x,y);
}

sf::Vector2f Tile::getPos() {
	return hiddenTile.getPosition();
}

sf::FloatRect Tile::GetSpriteRect() {
	return hiddenTile.getGlobalBounds();
}

//void Tile::DebugTile(sf::RenderWindow& window)
//{
//	if (isMine) {
//		window.draw(mine);
//	}
//}

void Tile::DrawMine(sf::RenderWindow& window)
{
	window.draw(mine);
}

void Tile::DrawFlag(sf::RenderWindow& window)
{
	window.draw(flaggedImage);
}