#pragma once


#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.h"

class Bullet
{
public:
	sf::RectangleShape      bulletBody;
	sf::Vector2f            velocity;
	float					projectileSpeed{};
	void                    update();
	void                    initialise(sf::Color t_bulletColor, sf::Vector2f t_bulletSize, float t_projectileSpeed);
	void                    fire(sf::Vector2f t_goalLocation,sf::Vector2f t_startPosition);
	sf::Clock               timeoutCounter;
	enum class              State { chambered, moving, fired };
	State                   bulletState{ State::chambered };
};

