#include "board.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Board::Board(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines)
{
	/*int cellNum = 0;
	vector<int> minedCells;
	vector<int> tempRow;*/

	_numMines = numMines;
	_numRows = numRows;
	_numCols = numCols;
	_numNotMines = (_numRows * _numCols) - _numMines;

	generateMines(numRows * numCols, _numMines);  // Generate random mines
	initializeTiles(textures, _numRows, _numCols, _numMines);
}

Board::Board(string boardType, map<string, sf::Texture>& textures)
{
	if (boardType == "1")
	{
		loadBoard("boards/testboard1.brd");
		_numNotMines = (_numRows * _numCols) - _numMines;
		initializeTiles(textures, _numRows, _numCols, _numMines);
	}
	else if (boardType == "2")
	{	
		cout << "Intitializing board 2" << endl;
		loadBoard("boards/testboard2.brd");
		_numNotMines = (_numRows * _numCols) - _numMines;
		initializeTiles(textures, _numRows, _numCols, _numMines);
	}
	else if (boardType == "3")
	{
		loadBoard("boards/testboard3.brd");
		_numNotMines = (_numRows * _numCols) - _numMines;
		initializeTiles(textures, _numRows, _numCols, _numMines);
	}
}

void Board::loadDefaultBoard(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines)
{
	_board.clear(); // Clear existing board
	_board.shrink_to_fit();
	_tileVector.clear();
	_tileVector.shrink_to_fit();

	_numMines = numMines;
	_numRows = numRows;
	_numCols = numCols;
	_numNotMines = (_numRows * _numCols) - _numMines;

	generateMines(numRows * numCols, _numMines);  // Generate random mines
	initializeTiles(textures, _numRows, _numCols, _numMines);
}

void Board::printBoard()
{
	for (int row = 0; row < _numRows; row++)
	{
		for (int col = 0; col < _numCols; col++)
		{
			cout << _board[row][col] << " ";

			if ((col % (_numCols - 1) == 0) and (col != 0))
				cout << endl;
		}
	}
}

void Board::generateMines(int numTiles, int numMines)
{
	int cellNum, i;
	vector<int> tempArr, tempRow;
	vector<int> minedCells;

	for (cellNum = 0; cellNum < numTiles; cellNum++) { // Populate array with 1 value for each tile number
		tempArr.push_back(cellNum);
	}

	// Shuffle all tile numbers to generate 'n' number which will be assigned with mines
	// Randomization method inspired by discussion found at https://stackoverflow.com/questions/20734774/random-array-generation-with-no-duplicates
	if (numTiles > 1)
	{
		/*mt19937 random_mt;
		uniform_int_distribution<int> dist(1, n);
		int i = dist(random_mt);*/

		srand(time(NULL));

		for (i = 0; i < numTiles - 1; i++)
		{
			int j = i + rand() / (RAND_MAX / (numTiles - i) + 1);
			int t = tempArr[j];
			tempArr[j] = tempArr[i];
			tempArr[i] = t;
		}

		for (int j = 0; j < numMines; ++j)  // Take first 'numMines' number of randomly shuffled cells to be mines
		{
			minedCells.push_back(tempArr[j]);
		}
	}

	_board.clear(); // Clear existing board
	tempRow.clear();

	for (int row = 0; row < _numRows; row++)
	{
		for (int col = 0; col < _numCols; col++)
		{
			cellNum = row * _numCols + col; // Formula to convert 2D row & col number to 1D cell number
			if (find(minedCells.begin(), minedCells.end(), cellNum) != minedCells.end()) {
				tempRow.push_back(1);
			}
			else {
				tempRow.push_back(0);
			}
		}

		_board.push_back(tempRow);
		tempRow.clear();
	}

}

//#pragma optimize( "", off )
void Board::loadBoard(string path)
{
	char nextChar;
	int nextVal;
	ifstream boardFile;
	int row = 0;
	int col = 0;

	_board.clear(); // Clear existing board
	_board.shrink_to_fit();
	_tileVector.clear();
	_tileVector.shrink_to_fit();

	//cout << "Opening board file... " << endl;
	boardFile.open(path);

	_numMines = 0;

	if (!boardFile.is_open())
		cout << "Cannot open board file to read." << endl;
	else
	{
		vector<int> tempArr;

		while(boardFile.get(nextChar))
		{		
			if (nextChar != '\n')
			{
				nextVal = int(nextChar) - 48;
				tempArr.push_back(nextVal);
				col++;

				if (nextVal == 1)
					_numMines++;
			}
			else if (nextChar == '\n')
			{
				_board.push_back(tempArr);

				tempArr.clear();
				row++;
				col = 0;
			}
		}

		_board.push_back(tempArr);  // Add last row at end of file to board

		_numRows = _board.size();
		_numCols = _board[0].size();
		_numNotMines = (_numRows * _numCols) - _numMines;
	}
}
//#pragma optimize( "", on ) 

void Board::initializeTiles(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines)
{
	_tileVector.clear();
	vector<Tile> tempRow;

	for (int row = 0; row < _numRows; row++)  // Set up board with mines in corners only
	{
		for (int col = 0; col < _numCols; col++)
		{
			/*if (_board[row][col] == 1) {
				++_numMines;
			}*/
			//if (_board[row][col] == 1) {
			//	cout << "Initializing bomb tile " << row << " " << col << endl;
			//}

			Tile newTile(_board[row][col], row, col, textures);

			tempRow.push_back(newTile); //.push_back(newTile);
		}

		_tileVector.push_back(tempRow);
		tempRow.clear();
	}


	for (int row = 0; row < _numRows; row++)  // Initialize adjacent tile vector for each tile
	{
		for (int col = 0; col < _numCols; ++col)
		{
			_tileVector[row][col].adjTileInit(_tileVector, row, _numRows, _numCols);
		}
	}

	for (int row = 0; row < _numRows; row++)  // Initialize number of adjacent mines
	{
		for (int col = 0; col < _numCols; ++col)
		{
			for (int i = 0; i < _tileVector[row][col]._adjacentTiles.size(); i++)
			{
				if (_tileVector[row][col]._adjacentTiles[i]->_mined) // If adjacent tile = mine, increment number of adjacent mines
					_tileVector[row][col]._numAdjacentMines++;
			}
		}
	}
}

void Board::drawBoard(sf::RenderWindow& screen, map<string, sf::Texture>& textures)
{

	for (int row = 0; row < _numRows; row++)  // Loop through each tile
	{
		for (int col = 0; col < _numCols; ++col)
		{
			_tileVector[row][col].drawTile(screen, textures);
		}

	}
}

void Board::debug(sf::RenderWindow& screen, map<string, sf::Texture>& textures)
{
	for (int row = 0; row < _numRows; row++)  // Loop through each tile
	{
		for (int col = 0; col < _numCols; ++col)
		{

			if ((_tileVector[row][col]._mined == true))
			{
				_tileVector[row][col]._debug = !(_tileVector[row][col]._debug);
			}

			_tileVector[row][col].drawTile(screen, textures);
		}
	}

}

void Board::resetBoard(map<string, sf::Texture>& textures)
{
	_tileVector.clear();
	initializeTiles(textures, _numRows, _numCols, _numMines);
	_numFlags = 0;
}