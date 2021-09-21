#pragma once
#include <SFML/Graphics.hpp>
class Platform
{

public:
	Platform();
	sf::RectangleShape platform;
	sf::Vector2f randomPos;
	void setupPlatform();
	sf::Vector2f velocity{ 0.0f, 0.0f };
	float speed = 1.0f;

private:
	sf::Vector2f size;

};