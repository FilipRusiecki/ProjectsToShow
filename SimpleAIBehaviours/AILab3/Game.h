
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wander.h"
#include "Seek.h"
#include "Flee.h"
#include "ArriveFast.h"
#include "ArriveSlow.h"
#include "Pursue.h"
class Game
{
public:
	Game();
	~Game();
	void run();
	Player myPlayer;
	Wander myWander;
	Seek mySeek;
	Flee myFlee;
	ArriveFast myArriveFast;
	ArriveSlow myArriveSlow;
	Pursue myPursue;

private:
	sf::Text info;
	sf::Font m_font;
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif 

