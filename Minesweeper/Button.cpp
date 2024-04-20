#include "Button.h"
#include <iostream>
using namespace std;

Button::Button()
{
	_position.x = 0;
	_position.y = 0;
}

Button::Button(float x, float y, string key, map<string, sf::Texture>& textures)
{
	_position.x = x;
	_position.y = y;
	
	_buttonSprite.setPosition(_position.x, _position.y);

	initializeTextures(key, textures);
}

void Button::initializeTextures(string key, map<string, sf::Texture>& textures)
{
	if (key == "smile")
	{
		_buttonTexture = textures[key];
		_buttonSprite.setTexture(_buttonTexture);
	}
	else if (key == "debug")
	{
		_buttonTexture = textures[key];
		_buttonSprite.setTexture(_buttonTexture);
	}
	else if (key == "test 1")
	{
		_buttonTexture = textures[key];
		_buttonSprite.setTexture(_buttonTexture);
	}
	else if (key == "test 2")
	{
		_buttonTexture = textures[key];
		_buttonSprite.setTexture(_buttonTexture);
	}
	else if (key == "test 3")
	{
		_buttonTexture = textures[key];
		_buttonSprite.setTexture(_buttonTexture);

	}

}

void Button::setButtonTexture(string key, map<string, sf::Texture>& textures)
{
	_buttonTexture = textures[key];
	_buttonSprite.setTexture(_buttonTexture);
}

void Button::drawButton(sf::RenderWindow& screen)
{
	_buttonSprite.setTexture(_buttonTexture);
	screen.mapCoordsToPixel(_buttonSprite.getPosition());
	screen.draw(_buttonSprite);

	_buttonBounds = _buttonSprite.getGlobalBounds();
}

void Button::setButtonPos(float x, float y)
{
	_position.x = x;
	_position.y = y;
	_buttonSprite.setPosition(_position.x, _position.y);
}

sf::Sprite Button::getSprite()
{
	return _buttonSprite;
}

sf::FloatRect Button::getBounds()
{
	return _buttonBounds;
}