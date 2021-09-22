#pragma once
#ifndef ZOMBIE
#define ZOMBIE


#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.h"
#include <iostream>
#include "MathUtility.h"
#include <Bullet.h>
#include "resourceHolder.h"
#include <SFML/Audio.hpp>
#include <queue>


class Grid;
class Cell;

class Zombie
{

public:

	
	sf::Clock bfsTimer;

	void init(resourceHolder& t_resources);
	void draw(sf::RenderWindow& t_window);
	void update(sf::Vector2f t_playerPos, int t_detectionRadius, sf::RectangleShape t_playerCollisionBox, int& t_playerHealth, Grid& t_grid, int t_cellPlayerIsIn);
	void animate();
	std::vector<int> breadthFirst(Grid t_grid, int& t_startCellId, int& t_destCellId);
	void setPosition(sf::Vector2f t_pos);
	sf::Vector2f getPosition();


	std::vector<int> m_path;
	bool goalReached = false;

	

	
	sf::Clock audioTimer;
	sf::Clock idleTimer;
	sf::Clock firingCooldown;
	void stopProjectile();

	void getCell(Grid& t_grid);
	Cell* cellZombieIsin;

	sf::Text zombieText;

	bool finishedAttacking = true;
	enum class State { searchAlgorithm, following, attacking };
	State currentState = State::searchAlgorithm;


	bool alive = true;


	float areaOrig;
	float area1;
	float area2;
	float area3;
	

	// Vision cone visualisation...vision cone origin


	Bullet zombieProjectile;



	sf::Sound zombieAttackSound;
	sf::Sound zombieBreathingSound;



	void turnToPlayer(sf::Vector2f t_playerPos);
	void processFollowPlayer(sf::Vector2f t_playerPos);
	void processIdle(sf::Vector2f t_playerPos);



	int aggroTime = 0;
	int aggroMaxTime = 360;
	float speed = 1.25f;
	int attackFrameCountDown = 0;
	const int ATTACKANIMATESPEED = 3;
	sf::RectangleShape collisionBox;
	int currentMoveFrame = 0;
	int currentAttackFrame = 0;
	int animateSpeed = 4;
	int frameCountDown = 0;
	const int AMOUNTTEXTURES = 16;
	const int AMOUNTATTACKTEXTURES = 9;
	sf::Texture zombieIdleTexture;
	sf::Sprite zombieSprite;
	sf::Texture zombieAttackTexture;
	sf::Texture zombieMoveTexture;
	sf::Vector2f velocity{ };
	int AMOUNTFRAMES = 19;
	
	sf::Vector2f zombieNextMovePosition;
	sf::Vector2f randomGoalPosition;
};
#endif//ZOMBIE
