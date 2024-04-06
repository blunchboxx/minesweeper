#include <iostream>
#include "tile.h"
using namespace std;

/*---- Constructors ----*/
Tile::Tile()
{
	_mined = false;
	_revealed = false;
	_flagged = false;
	_row = 0;
	_col = 0;
	_numAdjacentMines = 0;

}

Tile::Tile(int value, int row, int col, map<string, sf::Texture>& textures)
{
	_tileTexture = textures["hidden"];
	_mineTexture = textures["mined"];
	_flagTexture = textures["flagged"];

	_revealed = false;
	_flagged = false;
	_numAdjacentMines = 0;
	_row = row;
	_col = col;

	if (value == 1)
		_mined = true;
	else
		_mined = false;

}

Tile::Tile(const Tile& tile) // Copy constructor
{
	_tileTexture.loadFromFile("images/tile_hidden.png");
	_revealed = tile._revealed;
	_flagged = tile._flagged;
	_numAdjacentMines = tile._numAdjacentMines;
	_row = tile._row;
	_col = tile._col;
	_mined = tile._mined;

	for (int i = 0; i < tile._adjacentTiles.size(); i++)
	{
		_adjacentTiles.push_back(tile._adjacentTiles[i]);
	}
}

void Tile::adjTileInit(vector<vector<Tile>>& tileVector, int tileNum, int numRows, int numCols)
{	
	if (((_row != 0) and (_row != numRows - 1)) and ((_col != 0) and (_col != numCols - 1))) // If tile is not on edge or corner
	{
		for (int i = 0; i < 9; i++)
		{
			if (i < 3) // Find 3 tiles above tile
			{
				_adjacentTiles.push_back(&(tileVector[_row - 1][_col - 1 + i])); // 3 tiles above one row
			}
			else if ((i > 2) and (i < 6)) // Fine 2 tiles on same row
			{
				if (i == 4)  // Skip self tile
					continue;

				_adjacentTiles.push_back(&(tileVector[_row][_col - 4 + i])); // Tiles on same row on either side

			}
			else if (i > 5) // Find 3 tiles below tile
			{
				_adjacentTiles.push_back(&(tileVector[_row + 1][_col - 7 + i])); // 3 tiles on row below
			}
		}
	}

	else if (((_row == 0) and (_col == 0)) or ((_row == numRows - 1) and (_col == 0)) or ((_row == 0) and (_col == numCols - 1)) or ((_row == numRows - 1) and (_col == numCols - 1))) // If tile is corner
	{

		if ((_row == 0) and (_col == 0)) // For upper left corner
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col + 1])); // Next cell on same row
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col])); // Cell directly below
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col + 1])); // Cell diagonally below
		}
		else if ((_row == numRows - 1) and (_col == 0)) // For lower left corner
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col + 1])); // Next cell on same row
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col + 1])); // Cell diagonally above
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col])); // Cell directly above
		}
		else if ((_row == 0) and (_col == numCols - 1)) // For upper right corner
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col - 1])); // Previous cell on same row
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col - 1])); // Cell diagonally below
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col])); // Cell directly below
		}
		else if ((_row == numRows - 1) and (_col == numCols - 1)) // For lower right corner
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col - 1])); // Previous cell on same row
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col - 1])); // Cell diagonally above
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col])); // Cell directly above
		}		
	}

	else if ((_row == 0) or (_col == 0) or (_row == numRows - 1) or (_col == numCols - 1)) // If tile is on edge, but not corner
	{
		if (_row == 0) // If edge is top row
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col - 1])); // Previous cell on same row
			_adjacentTiles.push_back(&(tileVector[_row][_col + 1])); // Next cell on same row
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col - 1])); // Cell diagonally below to left
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col])); // Cell directly below
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col + 1])); // Cell diagonally below to right
		}
		else if (_col == 0) // If edge is left column
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col + 1])); // Next cell on same row
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col + 1])); // Cell diagonally above
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col])); // Cell above
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col + 1])); // Cell diagonally below
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col])); // Cell directly below			
		}
		else if (_col == numCols - 1) // If edge is right column
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col - 1])); // Previous cell on same row
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col - 1])); // Cell diagonally above
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col])); // Cell above
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col - 1])); // Cell diagonally below
			_adjacentTiles.push_back(&(tileVector[_row + 1][_col])); // Cell directly below	
		}
		else if (_row == numRows - 1) // If edge is bottom row
		{
			_adjacentTiles.push_back(&(tileVector[_row][_col - 1])); // Previous cell on same row
			_adjacentTiles.push_back(&(tileVector[_row][_col + 1])); // Next cell on same row
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col + 1])); // Cell diagonally above to right
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col])); // Cell directly above
			_adjacentTiles.push_back(&(tileVector[_row - 1][_col - 1])); // Cell diagonally above to left
		}
	}

}

void Tile::drawTile(sf::RenderWindow& screen, map<string, sf::Texture>& textures)
{
	if ((_revealed == false) and (_flagged == false) and (_mined == false)) // if tile is still hidden and not flagged
	{
		_tileSprite.setTexture(textures["hidden"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);
	}
	else if ((_revealed == false) and (_flagged == false) and (_mined == true) and (_debug == false)) // if tile is a mine that is still hidden and not flagged and not in debug mode
	{
		_tileSprite.setTexture(textures["hidden"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);
	}
	else if ((_revealed == false) and (_mined == true) and (_debug == true)) // if tile is a mine that is still hidden and not flagged and in debug mode
	{
		_tileSprite.setTexture(textures["hidden"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);

		_mineSprite.setTexture(textures["mined"]);
		_mineSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_mineSprite);
	}
	else if ((_revealed == true) and (_flagged == false) and (_numAdjacentMines == 0) and (_mined == false)) // if tile is revealed, has no adjacent mines and is not a mine
	{
		_tileSprite.setTexture(textures["revealed"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);
	}
	else if ((_revealed == true) and (_flagged == false) and (_numAdjacentMines > 0) and (_mined == false)) // if tile is clicked and is NOT a mine, but has adjacent mines
	{
		if (_numAdjacentMines == 1)
		{
			_tileSprite.setTexture(textures["1"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 2)
		{
			_tileSprite.setTexture(textures["2"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 3)
		{
			_tileSprite.setTexture(textures["3"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 4)
		{
			_tileSprite.setTexture(textures["4"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 5)
		{
			_tileSprite.setTexture(textures["5"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 6)
		{
			_tileSprite.setTexture(textures["6"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 7)
		{
			_tileSprite.setTexture(textures["7"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}
		else if (_numAdjacentMines == 8)
		{
			_tileSprite.setTexture(textures["8"]);
			_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
			screen.draw(_tileSprite);
		}

	}
	else if ((_revealed == true) and (_mined == true)) // if tile is clicked and is a mine
	{
		_tileSprite.setTexture(textures["revealed"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);

		_mineSprite.setTexture(textures["mined"]);
		_mineSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_mineSprite);
	}
	else if ((_revealed == false) and (_flagged == true))
	{
		_tileSprite.setTexture(textures["hidden"]);
		_tileSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_tileSprite);

		_flagSprite.setTexture(textures["flagged"]);
		_flagSprite.setPosition(_col * _tileSize, _row * _tileSize);
		screen.draw(_flagSprite);
	}

}

/*---- Operators ----*/
Tile& Tile::operator=(const Tile& rhs)
{
	if (this != &rhs)
	{
		_tileTexture = rhs._tileTexture;
		_revealed = rhs._revealed;
		_flagged = rhs._flagged;
		_numAdjacentMines = rhs._numAdjacentMines;
		_row = rhs._row;
		_col = rhs._col;
		_mined = rhs._mined;

		for (int i = 0; i < rhs._adjacentTiles.size(); i++)
		{
			_adjacentTiles.push_back(rhs._adjacentTiles[i]);
		}
	}

	return *this;
}

bool Tile::operator==(const Tile& rhs)
{
	if ((_row != rhs._row) or (_col != rhs._col))
		return false;
	else if ((_mined != rhs._mined) or (_numAdjacentMines != rhs._numAdjacentMines) or (_revealed = rhs._revealed) or (_flagged = rhs._flagged))
		return false;
	// FixMe, add _adjacentTiles comparison
	else
		return true;
}