#pragma once
#include <vector>
#include <string>
#include "tile.h"
using namespace std;


struct Board
{
	int _numMines = 0;
	int _numRows = 0;
	int _numCols = 0;
	int _numFlags = 0;
	int _numNotMines = 0;
	vector<vector<Tile>> _tileVector;
	map<pair<int, int>, Tile> _tileMap;
	vector<vector<int>> _board;

public:

	// Constructors
	Board(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines); // Randomized board constructor
	Board(string boardType , map<string, sf::Texture>& textures);  // Test board constructor

	// Debugging
	void printBoard();

	// Behavior
	void generateMines(int numTiles, int numMines);
	void loadBoard(string path);
	void loadDefaultBoard(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines);
	void initializeTiles(map<string, sf::Texture>& textures, int numRows, int numCols, int numMines);
	void drawBoard(sf::RenderWindow& screen, map<string, sf::Texture>& textures);
	void debug(sf::RenderWindow& screen, map<string, sf::Texture>& textures);
	void resetBoard(map<string, sf::Texture>& textures);
};

