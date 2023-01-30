#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
class Flee
{

public:
	sf::Texture m_fleeTexture;
	sf::Sprite m_fleeSprite;
	sf::CircleShape radius;
	float radiusF = 500.0f;
	void update(sf::Time& t_deltaTime, Player& t_player);
	void render(sf::RenderWindow& t_window);
	Flee();
	bool alive = false;
	bool tracerAlive = false;
	void flee(sf::Time& t_deltaTime, Player& t_player);
	sf::RectangleShape leftLine;
	sf::RectangleShape rightLine;
	float angleOfSight = 35;
	sf::Vector2f norm(sf::Vector2f vec);
private:
	sf::Font m_font;
	sf::Text nameTag;
	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 2.0f;
	float maxSpeed = 1.0f;
	float distance;
	float timeToTarget = 0.25f;
	float GetProperRot;
	float rotation;
	int offSetOffScreen = 16;
	sf::Vector2f distanceVec;
	sf::Vector2f vel;
	void setupSprites();
	void boundry();

};