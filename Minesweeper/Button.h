#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Button
{
public:
	Button();
	Button(float x, float y, string key, map<string, sf::Texture>& textures);

	void drawButton(sf::RenderWindow& screen);
	void initializeTextures(string key, map<string, sf::Texture>& textures);
	void setButtonTexture(string key, map<string, sf::Texture>& textures);
	void setButtonPos(float x, float y);

	// Getters
	sf::Sprite getSprite();
	sf::FloatRect getBounds();

	sf::Texture _buttonTexture;
	sf::Texture normalButtonTexture;
	sf::Texture clickedButtonTexture;
	sf::Texture gameOverButtonTexture;
	sf::Texture gameWinButtonTexture;
	sf::Texture debugButtonTexture;
	sf::Texture test1ButtonTexture;
	sf::Texture test2ButtonTexture;
	sf::Texture test3ButtonTexture;


	sf::Sprite _buttonSprite;
	sf::Vector2f _position;
	sf::FloatRect _buttonBounds;

};

