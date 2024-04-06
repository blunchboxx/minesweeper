#include "Digit.h"

Digit::Digit()
{
	_position.x = 0;
	_position.y = 0;

	_digitSprite.setPosition(_position.x, _position.y);
}

Digit::Digit(float x, float y, map<string, sf::Texture>& textures)
{
	_position.x = x;
	_position.y = y;
	_digitSprite.setPosition(_position.x, _position.y); // Set counter digit location

	_digitTexture = textures["digits"]; // Set counter digit texture to entire digit image
	initializeRects(textures); // Generate all possible texture rects for each number

	_digitSprite.setTextureRect(_digitRects[0]); // Initialize texture rect to display number zero
	_digitCurrRect = _digitSprite.getTextureRect(); // Set current rectangle. Retains correct digit value between draws
}

void Digit::initializeRects(map<string, sf::Texture>& textures)
{
	int xCoord = 0;


	for (int i = 0; i < 11; ++i) {

		sf::IntRect nextRect(xCoord, 0, 21, 32);
		_digitRects.emplace(i, nextRect);
		
		xCoord += 21;
	}
}

void Digit::setDigitPos(float x, float y)
{
	_position.x = x;
	_position.y = y;
	_digitSprite.setPosition(_position.x, _position.y);
}

void Digit::setDigitDisplay(int num)
{
	_digitSprite.setTexture(_digitTexture);
	_digitSprite.setTextureRect(_digitRects[num]);
	_digitCurrRect = _digitSprite.getTextureRect();
}

void Digit::drawDigit(int val, sf::RenderWindow& screen) 
{
	_digitSprite.setTexture(_digitTexture);
	_digitSprite.setTextureRect(_digitCurrRect);
	screen.mapCoordsToPixel(_digitSprite.getPosition());
	screen.draw(_digitSprite);
}
