#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Player{
public:
		
	sf::CircleShape circle;


	Player();
	void init();
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);

private:


};