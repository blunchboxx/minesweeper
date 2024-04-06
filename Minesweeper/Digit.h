#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

struct Digit
{
	Digit();
	Digit(float x, float y, map<string, sf::Texture>& textures);
	void initializeRects(map<string, sf::Texture>& textures);
	void setDigitDisplay(int num);
	void drawDigit(int val, sf::RenderWindow& screen);
	void setDigitPos(float x, float y);


	map<int, sf::IntRect> _digitRects;

	sf::Vector2f _position;

	sf::Texture _digitTexture;
	sf::IntRect _digitCurrRect;
	sf::Sprite _digitSprite;
};

