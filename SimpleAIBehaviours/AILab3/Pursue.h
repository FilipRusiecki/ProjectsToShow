#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
class Pursue
{
public:
	sf::Texture m_pursueTexture; // texture used for alien
	sf::Sprite m_pursueSprite; // sprite used for alien
	sf::VertexArray LineToPlayer{ sf::Lines };

	void update(sf::Time& t_deltaTime, Player& t_player);
	void render(sf::RenderWindow& t_window);
	Pursue();
	bool alive = false;
	bool tracerAlive = false;
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
	float maxSpeed = 4.0f;
	float distance;
	float timeToTarget = 0.25f;
	float GetProperRot;
	float rotation;
	sf::Vector2f distanceVec;
	sf::Vector2f vel;

	void setupSprites();
	void pursue(sf::Time& t_deltaTime, Player& t_player);


};

