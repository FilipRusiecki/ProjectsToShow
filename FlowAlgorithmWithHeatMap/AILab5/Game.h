
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	Grid m_grid;
	sf::Vector2i mousePosition;

private:
	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);

	void update(sf::Time t_deltaTime);
	void render();
	
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif 

