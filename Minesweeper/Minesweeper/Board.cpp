#include "Board.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Random.h";

using namespace std;


Board::Board(int& col, int& row, int& mine) {
	numCol = col; 
	numRow = row;
    mineCount = mine;
    flagCounter = mine;
    isLossed = false;
    revealCounter = 0;
    won = false;
    debuggerOn = false;

     //counterDisplay.setTexture(TextureManager::GetTexture("digits.png"));

	//fileName = file_Name;
    //Tile hiddenTiles[numCol][numRow];

}

//inside main while loop,


void Board::Create() {
    
    int tempY = 0;
    for (int i = 0; i < numRow; i++) {
        vector<Tile> eachRow;
        for (int j = 0; j < numCol; j++) {
            Tile hidden("tile_hidden");
            hidden.setPos(j * hidden.getWidth(), tempY);
            //hidden.Display(window);
            eachRow.push_back(hidden);
           
        }
        cout << eachRow.size() << endl;
        cout << numRow << endl;
        cout << "spam :" << endl;
        Tile tempTile("tile_hidden");
        tempY += tempTile.getHeight();
        tiles.push_back(eachRow);
    }

    int  k = 0;
    while (k < mineCount) {
        int tileRow = Random::Int(0, numRow - 1);
        int tileCol = Random::Int(0, numCol - 1);

        if (tiles[tileRow][tileCol].isMine) {
            continue;
        }
        else {
            tiles[tileRow][tileCol].isMine = true;
        }

        /* for (int k = 0; k < numOfMine; k++) {
             boardObj.tiles[Random::Int(0, row - 1)][Random::Int(0, col - 1)].isMine = true;*/



        k++;
    }



   /* sf::Sprite smileyFace(TextureManager::GetTexture("face_happy"));
    smileyFace.setPosition((numCol * 32) / 2.0f, numRow * 32);
    window.draw(smileyFace);*/


    //sf::Vector2f position = smileyFace.getPosition();



  /*  sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    int debugXPos = 2 * (smileyFace.getGlobalBounds().width) + position.x;

    debugButton.setPosition(debugXPos, numRow * 32);
    window.draw(debugButton);

    int tempX = debugXPos + smileyFace.getGlobalBounds().width;


    for (int i = 1; i <= 3; i++) {
        string testBoardName = "test_" + to_string(i);
        sf::Sprite testBoard(TextureManager::GetTexture(testBoardName));
        testBoard.setPosition(tempX, numRow * 32);
        window.draw(testBoard);

        tempX += smileyFace.getGlobalBounds().width;
    }*/

}


void Board::clear( int mine) {
    //tiles.clear();

    if (debuggerOn) {


    int tempY = 0;
    for (int i = 0; i < numRow; i++) {
        vector<Tile> eachRow;
        for (int j = 0; j < numCol; j++) {
            Tile hidden("tile_hidden");
            hidden.setPos(j * hidden.getWidth(), tempY);
            //hidden.Display(window);
            eachRow.push_back(hidden);

        }
        cout << eachRow.size() << endl;
        cout << numRow << endl;
        cout << "spam :" << endl;
        Tile tempTile("tile_hidden");
        tempY += tempTile.getHeight();
        tiles.push_back(eachRow);
    }

    int  k = 0;
     while (k < mineCount) {
        int tileRow = Random::Int(0, numRow - 1);
        int tileCol = Random::Int(0, numCol - 1);

        if (tiles[tileRow][tileCol].isMine) {
            continue;
        }
        else {
            tiles[tileRow][tileCol].isMine = true;
        }





        k++;
     }
    } 
    else {
        tiles.clear();
        int tempY = 0;
        for (int i = 0; i < numRow; i++) {
            vector<Tile> eachRow;
            for (int j = 0; j < numCol; j++) {
                Tile hidden("tile_hidden");
                hidden.setPos(j * hidden.getWidth(), tempY);
                //hidden.Display(window);
                eachRow.push_back(hidden);

            }
            cout << eachRow.size() << endl;
            cout << numRow << endl;
            cout << "spam :" << endl;
            Tile tempTile("tile_hidden");
            tempY += tempTile.getHeight();
            tiles.push_back(eachRow);
        }

        int  k = 0;
        while (k < mineCount) {
            int tileRow = Random::Int(0, numRow - 1);
            int tileCol = Random::Int(0, numCol - 1);

            if (tiles[tileRow][tileCol].isMine) {
                continue;
            }
            else {
                tiles[tileRow][tileCol].isMine = true;
            }





            k++;
        }
    }


    isLossed = false;
    flagCounter = mine;
    mineCount = mine;
}

//
//void Board::DisplayCounter(sf::RenderWindow& window) {
//    window.draw(counterDisplay);
//}

//possibly make a debug function using code similar to yours

//window.draw(hiddenTile);

//probably pass in a file name
void Board::testBoard(string filename) {
    tiles.clear();


    ifstream inFile(filename);
    string numString;

    int rowNum = 0;
    int colNum;

    while (inFile >> numString)
    {

        colNum = numString.size();

        rowNum++;

    }

    numCol = colNum;
    numRow = rowNum;


    int tempY = 0;
    for (int i = 0; i < rowNum; i++) {
        vector<Tile> eachRow;
        for (int j = 0; j < colNum; j++) {
            Tile hidden("tile_hidden");
            hidden.setPos(j * hidden.getWidth(), tempY);
            //hidden.Display(window);
            eachRow.push_back(hidden);

        }
        cout << eachRow.size() << endl;
        cout << rowNum << endl;
        cout << "spam :" << endl;
        Tile tempTile("tile_hidden");
        tempY += tempTile.getHeight();
        tiles.push_back(eachRow);
    }

    //ifstream inFile("boards/testboard1.brd");
   // string numString;


    inFile.close();
    inFile.clear();
    inFile.open(filename);
    //int colNum;

     rowNum = 0;
    mineCount = 0;
     
    while (inFile >> numString)
    {



        for (int i = 0; i < numString.size(); i++) {
            if (numString[i] == '1') {
            //colNum = i;
             tiles[rowNum][i].isMine = true;
             mineCount++;
            }

        }

        rowNum++;

    }
    



   // tiles[0][0].isMine = true;


    isLossed = false;
    flagCounter = mineCount;
    //mineCount = 1;



}



//void Board::DebuggerOn() {
//    
//}