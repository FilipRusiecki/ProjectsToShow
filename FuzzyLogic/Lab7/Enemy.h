#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Enemy {
public:

	sf::CircleShape circle;


	Enemy();
	void init();
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);
	bool alive = false;
private:


};