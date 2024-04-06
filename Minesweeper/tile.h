#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

struct Tile
{
	sf::Sprite _tileSprite;
	sf::Sprite _mineSprite;
	sf::Sprite _flagSprite;
	sf::Texture _mineTexture;
	sf::Texture _flagTexture;
	sf::Texture _tileTexture;
	/*sf::Texture hiddenTileTexture;
	
	sf::Texture revealedTileTexture;
	sf::Texture flaggedTileTexture;
	sf::Texture mineTileTexture;
	sf::Texture numOneTexture;
	sf::Texture numTwoTexture;
	sf::Texture numThreeTexture;
	sf::Texture numFourTexture;
	sf::Texture numFiveTexture;
	sf::Texture numSixTexture;
	sf::Texture numSevenTexture;
	sf::Texture numEightTexture;*/
	bool _mined = false;
	bool _revealed = false;
	bool _flagged = false;
	bool _debug = false;
	int _row = 0;
	int _col = 0;
	int _numAdjacentMines = 0;
	vector<Tile*> _adjacentTiles;
	const int _tileSize = 32;

public:

	Tile();
	Tile(int value, int row, int col, map<string, sf::Texture>& textures);
	Tile(const Tile& tile);

	void adjTileInit(vector<vector<Tile>>& tileVector, int tileNum, int numRows, int numCols);

	void drawTile(sf::RenderWindow& screen, map<string, sf::Texture>& textures);

	/*---- Operators ----*/
	Tile& operator=(const Tile& rhs);
	bool operator==(const Tile& rhs);
};

