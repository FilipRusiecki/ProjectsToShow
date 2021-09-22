#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Weather
{

public:
	sf::Texture snowTexture;
	const static int amountPrecipitation = 600;

	sf::Vector2f velocity[amountPrecipitation];
	sf::Sprite precipitationSprite[amountPrecipitation];
	sf::Vector2i windowSize{ 1920,1080 };
	sf::Vector2i windowEnds{ 0,0 };
	sf::RectangleShape black;

	void init();
	void draw(sf::RenderWindow& t_window);
	void update(sf::RenderWindow& t_window);
};

