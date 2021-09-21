#pragma once
#include <SFML/Graphics.hpp>

class player {


public:
	sf::Vector2f velocity{ 0.0f, 0.0f };
	sf::Vector2f size{ 20.0f,20.0f };
	sf::RectangleShape shape;

	sf::Clock clock;
	float speed = 150.0f;

	sf::Vector2f gravity{0.0f, 9.8f  };

	void playerConst();

};