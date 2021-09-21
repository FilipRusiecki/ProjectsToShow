#pragma once
#include <SFML/Graphics.hpp>
class Smudge {

public:
	Smudge();
	sf::Vector2f velocity{ 0.0f, 0.0f };
	sf::RectangleShape playerSmudge;
	sf::Vector2f size{ 12.0f,12.0f };
	float speed = 5.0f;
	void setupSmudge();
}
;