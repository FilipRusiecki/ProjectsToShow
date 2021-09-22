#pragma once
#include "Instructions.h"
#include "Globals.h"
class CharacterCustomization {
	sf::Sprite bgSprite;
	sf::Texture bgTexture;

	sf::RectangleShape greenBox;
	sf::RectangleShape skin1;
	sf::RectangleShape skin2;
	sf::RectangleShape skin3;
	sf::RectangleShape skin4;

	sf::Sprite player1;
	sf::Texture playerTexture1;

	sf::Sprite player2;
	sf::Texture playerTexture2;

	sf::Sprite player3;
	sf::Texture playerTexture3;

	sf::Sprite player4;
	sf::Texture playerTexture4;
	sf::Font m_font;

	sf::Text arrowUp;
	sf::Text arrowDown;
	sf::Text arrowLeft;
	sf::Text arrowRight;

public:
	void		init();
	void		draw(sf::RenderWindow&);
	void		update();
	void		loadContent();
	int			selectedSkin = 0;
	int			getSkin();
};