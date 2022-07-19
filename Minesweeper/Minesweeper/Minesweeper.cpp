#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include<fstream>
#include <string>
#include <vector>
#include <cmath>
#include "TextureManager.h"
#include "Random.h"
#include "Tile.h"
#include "Board.h"

using namespace std;
void OpenConfigFile(string filePath, int& numCol, int& numRow, int& numMine);


void OpenConfigFile(string filePath, int& numCol, int& numRow, int& numMine) {

    ifstream inFile(filePath);

    if (inFile.is_open()) {
        string fileLine;

          getline(inFile, fileLine);
          numCol = stoi(fileLine);

          getline(inFile, fileLine);

          numRow = stoi(fileLine);
          getline(inFile, fileLine);
          numMine = stoi(fileLine);


        
    }

    else {
        cout << "File did not open" << endl;
    }

}


//possibly have a counter of the number of tiles you have revealed 

int main()
{

    int col = 0;
    int row = 0;
    int numOfMine = 0;
    
   bool isTestBoard = false;

    


 // bool flagOn = false;

    OpenConfigFile("boards/config.cfg", col, row, numOfMine);
   // ReadTestBoard
  
    //bool clickWIn = false;
   // bool won = false;

    Board boardObj(col, row, numOfMine);
    int tileCount = col * row;

    sf::RenderWindow window(sf::VideoMode(col * 32, (row * 32) + 88), "Minesweeper");


  //  numOfMine = 3;
    

   // sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));

    

    sf::Sprite smileyFace(TextureManager::GetTexture("face_happy"));
    smileyFace.setPosition((col * 32) / 2.0f, row * 32);

    sf::Vector2f position = smileyFace.getPosition();

    sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
    loseFace.setPosition(position.x, position.y);

    sf::Sprite winFace(TextureManager::GetTexture("face_win"));
    winFace.setPosition(position.x, position.y);

    sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    int debugXPos = 2 * (smileyFace.getGlobalBounds().width) + position.x;

    sf::Sprite  flag(TextureManager::GetTexture("flag"));



    int tempX = debugXPos + smileyFace.getGlobalBounds().width;

    string testBoardName1 = "test_" + to_string(1);
    sf::Sprite testBoard1(TextureManager::GetTexture(testBoardName1));
    testBoard1.setPosition(tempX, row * 32);
    window.draw(testBoard1);

    tempX += smileyFace.getGlobalBounds().width;
    string testBoardName2 = "test_" + to_string(2);
    sf::Sprite testBoard2(TextureManager::GetTexture(testBoardName2));
    testBoard2.setPosition(tempX, row * 32);
    window.draw(testBoard2);

    tempX += smileyFace.getGlobalBounds().width;
    string testBoardName3 = "test_" + to_string(3);
    sf::Sprite testBoard3(TextureManager::GetTexture(testBoardName3));
    testBoard3.setPosition(tempX, row * 32);
    window.draw(testBoard3);

    debugButton.setPosition(debugXPos, row * 32);



    //placement of mineDisplay counter

    int displayPosX = position.x - (6 * smileyFace.getGlobalBounds().width);

    sf::Sprite negativeSprite(TextureManager::GetTexture("digits"));
    negativeSprite.setPosition(displayPosX, row * 32);   

    sf::Sprite hundredSprite(TextureManager::GetTexture("digits"));
    hundredSprite.setPosition(displayPosX + 21, row * 32);    
    sf::Sprite tenSprite(TextureManager::GetTexture("digits"));
    tenSprite.setPosition(displayPosX + 42, row * 32);    
   sf::Sprite oneSprite(TextureManager::GetTexture("digits"));
    oneSprite.setPosition(displayPosX + 63, row * 32);

    boardObj.Create();


    //before the smileyface put a for loop that loops through everything 
    //then call tile display function.

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);


                    if (smileyFace.getGlobalBounds().contains(position.x, position.y))
                    {
                        if (isTestBoard) {
                            boardObj.clear(numOfMine);
                            isTestBoard = false;
                        }

                        //if (flagOn) {

                        //    // flagOn = false;
                        //boardObj.clear(numOfMine);
                        //}

                        //won = false;
                        
                       boardObj.won = false;
                        boardObj.revealCounter = 0;

                        boardObj.isLossed = false;
                        boardObj.clear(numOfMine);
                       // boardObj.mineCount = numOfMine;
                     //   isTestBoard = false;

                    }

                    if (testBoard1.getGlobalBounds().contains(position.x, position.y)) {
                        boardObj.testBoard("boards/testboard1.brd"); //pass in filename to get files and then possibly creates your own tile class
                        cout << "test board 1" << endl;
                      isTestBoard = true;
                    }

                    if (testBoard2.getGlobalBounds().contains(position.x, position.y)) {
                        boardObj.testBoard("boards/testboard2.brd");
                        cout << "test board 2" << endl;

                        isTestBoard = true;
                    }

                    if (testBoard3.getGlobalBounds().contains(position.x, position.y)) {
                        boardObj.testBoard("boards/testboard3.brd");
                        cout << "test board 3" << endl;

                        isTestBoard = true;

                    }

                    for (int i = 0; i < boardObj.tiles.size(); i++) {//rows
                        for (int j = 0; j < boardObj.tiles[i].size(); j++) {
                            if (boardObj.tiles[i][j].GetSpriteRect().contains(position.x, position.y) && boardObj.tiles[i][j].isFlagged) { //if we click on a flagged tile it cannot be revealed
                                boardObj.tiles[i][j].isRevealed = false;
                            }
                            else if(boardObj.tiles[i][j].GetSpriteRect().contains(position.x, position.y)){ //if not flagged then it will be revealed
                                boardObj.tiles[i][j].isRevealed = true;


                                if (numOfMine > 0) {
                                    if (boardObj.tiles[i][j].isMine) { //if a revealed and if a mine then game is lost
                                       // boardObj.tiles[i][j].isRevealed = true;
                                        //boardObj.mineCount--; //might not be useful
                                       // boardObj.tiles[i][j].isDebugged = true; 
                                        boardObj.isLossed = true;
                                        //boardObj.flagCounter = 0; // to affect the display
                                    }
                                    else {
                                        boardObj.revealCounter++;
                                    }
                                    cout << "Flag count: " << boardObj.flagCounter << endl; //should print out 0 
                                    cout << "Number of mines left: " << boardObj.mineCount << endl;
                                }
                                else {
                                    // boardObj.tiles[i][j].isMine = false;
                                    cout << "No more mines" << endl;
                                }
                                cout << "X: " << position.x << " Y: " << position.y << endl;
                                cout << "i: " << i << " j: " << j << endl;
                                cout << "number of rows: " << boardObj.tiles.size() << endl;
                                cout << "number of columns: " << boardObj.tiles[i].size() << endl;
                            }
                        }

                    }


                    //debugger should not work
                    if (boardObj.isLossed) {
                        continue;
                    }
                    else if (boardObj.won) {
                        continue;
                    }
                    else if (debugButton.getGlobalBounds().contains(position.x, position.y)) {
                        //boardObj.isLossed = false;
                        //won = false;
                        boardObj.debuggerOn = !boardObj.debuggerOn;
                            for (int i = 0; i < boardObj.tiles.size(); i++) {
                                for (int j = 0; j < boardObj.tiles[i].size(); j++) {
                                    boardObj.tiles[i][j].isDebugged = !boardObj.tiles[i][j].isDebugged;  //
                                    //boardObj.tiles[i][j].isMine = true;
                                }
                            }
                                    cout << "debug button" << endl;
                        }
                    

                    
                }

                //should stop flagging if we lost game, but we may have
                if (boardObj.isLossed) {
                    continue;
                }  

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    

                        for (int i = 0; i < boardObj.tiles.size(); i++) {//rows
                            for (int j = 0; j < boardObj.tiles[i].size(); j++) {

                                if (boardObj.tiles[i][j].GetSpriteRect().contains(position.x, position.y) && boardObj.tiles[i][j].isRevealed) {
                                    boardObj.tiles[i][j].isFlagged = false;
                                }
                                else if (boardObj.tiles[i][j].GetSpriteRect().contains(position.x, position.y)) {
                                    boardObj.tiles[i][j].isFlagged = !boardObj.tiles[i][j].isFlagged;
                                    if (boardObj.tiles[i][j].isFlagged) {
                                        boardObj.flagCounter--;
                                    }
                                    else {
                                        boardObj.flagCounter++;
                                    }
                                    cout << "X: " << position.x << " Y: " << position.y << endl;
                                    cout << "i: " << i << " j: " << j << endl;
                                    cout << "flag counter: " << boardObj.flagCounter << endl;
                                    /*cout << "number of rows: " << boardObj.tiles.size() << endl;
                                    cout << "number of columns: " << boardObj.tiles[i].size() << endl;*/
                                }

                            }
                        }
              
                }


            }

        }


        window.clear(sf::Color(255,255,255)); //changes the background color (defaults to black))

 
        for (int i = 0; i < boardObj.tiles.size(); i++) {//rows
            for (int j = 0; j < boardObj.tiles[i].size(); j++) {
                boardObj.tiles[i][j].Display(window);

            }
        }

      

        for (int i = 0; i < boardObj.tiles.size(); i++) {//rows
            for (int j = 0; j < boardObj.tiles[i].size(); j++) {
                if (boardObj.isLossed && boardObj.tiles[i][j].isMine) {
                boardObj.tiles[i][j].DrawMine(window);
                }

            }
        }
        

      //  boardObj.Display(window);

        //if we lose the game then we print the lose face, else we go back to the smileyface

        if (boardObj.revealCounter == (tileCount - boardObj.mineCount) && !boardObj.isLossed) {
            boardObj.won = true;
        }


        if (boardObj.won) {

            window.draw(winFace);
         }
        else if (boardObj.isLossed) {
            window.draw(loseFace);
        }
        else if(!boardObj.isLossed  && !boardObj.won) {
        window.draw(smileyFace);
      }


        if (boardObj.won) {
            for (int i = 0; i < boardObj.tiles.size(); i++) {//rows
                for (int j = 0; j < boardObj.tiles[i].size(); j++) {
                    if (boardObj.tiles[i][j].isMine) {
                        boardObj.tiles[i][j].DrawFlag(window);
                        boardObj.flagCounter = 0;
                        //boardObj.tiles[i][j].DrawMine(window);
                    }

                }
            }
        }

      //  debugButton.setPosition(debugXPos, row * 32);
        window.draw(debugButton);

        window.draw(testBoard1);
        window.draw(testBoard2);
        window.draw(testBoard3);

        int onesPlace;
        int tensPlace;
        int hundredsPlace;
     //   boardObj.DisplayCounter(window);

        if (boardObj.flagCounter >= 0) {
            onesPlace = boardObj.flagCounter % 10;
            tensPlace = (boardObj.flagCounter / 10) % 10;
            hundredsPlace = boardObj.flagCounter / 100;
            oneSprite.setTextureRect(sf::IntRect(21 * onesPlace, 0, 21, 32));
            tenSprite.setTextureRect(sf::IntRect(21 * tensPlace, 0, 21, 32));
            hundredSprite.setTextureRect(sf::IntRect(21 * hundredsPlace, 0, 21, 32));

        }
        else if (boardObj.flagCounter < 0) {
            onesPlace = abs(boardObj.flagCounter) % 10;
            tensPlace = (abs(boardObj.flagCounter) / 10) % 10;
            hundredsPlace = abs(boardObj.flagCounter) / 100;
            oneSprite.setTextureRect(sf::IntRect(21 * onesPlace, 0, 21, 32));
            tenSprite.setTextureRect(sf::IntRect(21 * tensPlace, 0, 21, 32));
            hundredSprite.setTextureRect(sf::IntRect(21 * hundredsPlace, 0, 21, 32));
            negativeSprite.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
        }

        if (boardObj.flagCounter < 0) {

            window.draw(negativeSprite);
            window.draw(oneSprite);
            window.draw(tenSprite);
            window.draw(hundredSprite);
        }
        else {
            window.draw(oneSprite);
            window.draw(tenSprite);
            window.draw(hundredSprite);
        }



        window.display();
    }

    TextureManager::Clear();

    cout << "Number of Columns: " << col << endl;
    cout << "Number of Rows: " << row << endl;
    cout << "Number of mines: " << numOfMine << endl;
    cout << "Number of tiles: " << tileCount << endl;

    return 0;
}