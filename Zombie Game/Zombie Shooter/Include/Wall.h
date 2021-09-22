#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Zombie.h"
#include "VectorAlgebra2D.h"
#include "MathUtility.h"

class Wall
{
public:
	Wall(sf::Vector2f position, int t_width, int t_height)
	{
		body.setSize(sf::Vector2f(t_width,t_height));
		body.setPosition(position);
		body.setFillColor(sf::Color::Magenta);
		body.setOrigin(t_width / 2, t_height / 2);
	}
	sf::RectangleShape body;
	sf::Vector2f lastKnownPlayerPos;
	sf::Vector2f lastKnownZombiePos;
	void checkCollisionsWithPlayer(Player &t_player);
	void checkCollisionsWithEnemy(Zombie &t_zombie);
	void draw(sf::RenderWindow& t_window);
	bool isOuter = false;
};

