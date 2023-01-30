#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{

public:
	sf::Texture m_playerTexture; // texture used for player
	sf::Sprite m_playerSprite; // sprite used for player
	sf::VertexArray playerLine{ sf::Lines };
	sf::VertexArray playerVisLeft{ sf::Lines };
	sf::VertexArray playerVisRight{ sf::Lines };

	sf::Vector2f linePoint;
	sf::Vector2f visPointLeft;
	sf::Vector2f visPointRight;

	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;
	float angleOfSight = 35;

	sf::Vector2f PursuePointCenter;
	sf::CircleShape radius;
	sf::CircleShape radiusSmaller;
	sf::CircleShape pursuePoint;

	float radiusF = 60.0f;
	float radiusFSmall = 30.0f;
	float pursuePointRadius = 50.0f;


	Player();
	void update(sf::Time& t_deltaTime);
	void render(sf::RenderWindow& t_window);
	bool tracerAlive = false;
	float speed = 0.0f;
	void playerMovement(sf::Time& t_deltaTime);
	float angle;
	float rotation = 90;
	float angleInRadsLeft = 0;
	float angleInRadsRight = 0;
	float pi = 3.141592653589793238f;

private:
	int playerOffset = 16;
	float angleInRads = 0;

	sf::Vector2f vel;
	sf::Vector2f vel2;
	float maxSpeedFront = 8.0f;
	float maxSpeedReverse = -8.0f;
	float GetProperRot;
	bool turnLeft = false;
	bool turnRight = false;
	void setupSprites();
	void boundry();
};

