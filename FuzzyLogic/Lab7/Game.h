
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <algorithm>

class Game
{
public:
	Game();
	~Game();
	Player myPlayer;
	Enemy myEnemy[30];

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();
	int randomAmountOfEnemies;
	float Y = 100;
	void spreadEnemies();
	void reset();
	void threatLevelApplication();
	void settingRangeAndForce();
	void defuzzification();
	bool resetEnemies = false;
	double FuzzyTrapezoid(double v, double x0, double x1, double x2, double x3);
	double FuzzyTriangle(double v, double x0, double x1, double x2);
	double FuzzyGrade(double v, double x0, double x1);


	double FuzzyAND(double A, double B);
	double FuzzyOR(double A, double B);
	double FuzzyNOT(double A);

	int force;
	double tinyForce;
	double smallForce;
	double moderateForce;
	double largeForce;

	int range;
	double closeRange;
	double mediumRange;
	double largeRange;

	double lowDanger;
	double moderateDanger;
	double highDanger;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // font used by message
	sf::Text m_message; // text used for message on screen
	sf::Text m_message1;

	sf::RectangleShape UiBox;
	sf::Text Ui1;
	sf::Text Ui2;
	sf::Text Ui3;
	sf::Text Ui4;
	sf::Text Ui5;
	sf::Text Ui6;
	sf::Text Ui7;
	sf::Text Ui8;
	sf::Text Ui9;
	sf::Text Ui10;
	sf::Text Ui11;
	sf::Text Ui12;
	sf::Text Ui13;





	sf::Texture m_logoTexture; // texture used for sfml logo
	bool m_exitGame; // control exiting game

};

#endif 
