#pragma once
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class instructions {
private:
	sf::Sprite bgSprite;
	sf::Texture bgTexture;


	sf::Sprite wasdSprite;
	sf::Texture wasdTexture;


	sf::Sprite shiftSprite;
	sf::Texture shiftTexture;

	sf::Sprite rSprite;
	sf::Texture rTexture;


	sf::Sprite escSprite;
	sf::Texture escTexture;


	sf::Text wKey;
	sf::Text aKey;
	sf::Text sKey;
	sf::Text dKey;
	sf::Text shiftKey;
	sf::Text rKey;
	sf::Text escKey;
	sf::Font m_font;

public:
	void init();
	void draw(sf::RenderWindow&);
	void update();
	void loadContent();



};