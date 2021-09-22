#pragma once
#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.h"
#include "Bullet.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <CharacterCustomization.h>
#include "PlayerDrawables.h"
#include "PlayerAudio.h"



class Player
{
private:
	

	


	

	

	//audio class
	PlayerAudio playerAudio;
	//graphics class




	int amountBloodStainsOut = 0;
	//*************TODO FIX BLOODSTAINS, PROGRAM WILL CRASH*****************

	//detection variables
	sf::Vector2f        detectOrigin{};
	const int           NOTMOVINGDETECTION = 750;
	const int           MOVINGDETECTION = 750;
	const int           SPRINTINGDETECTION = 750;
	




	sf::Clock			bloodTrailTimer;

	sf::Vector2f		playerRotationAngle;// polar angle between mouse position and player position
	//UI element variables
	sf::Text            playerText;// text object for player speech 
	sf::Font            playerFont;// font for player text
	std::string         playerString;//string for player text
	sf::RectangleShape	stamBar;//stamina bar
	int					textTimeOut = 0;//text disappearing counter
	const int			MAXTEXTTIMEOUT = 120;//how long text stays active
	sf::Text			UItext; //UI debug text
	sf::Font			UIfont;// font for UI


	//*****Gameplay variables*****
	//shooting and reloading 
	
	
	int					rateOfFireLimit = 0;
	
	int					ammoInMag = 30;
	int					ammoInReserve = 20;
	int					reloadTimer = 120;
	bool				reloading = false;
	const int			ROFTIMEOUTCAP = 6;
	//movement variables
	
	const float			playerSpeed = 2;
	const float			MAXSTAMINA = 120;
	float				currentStamina = MAXSTAMINA;
	bool				moving = false;
	


	
	sf::Vector2f		mouseRelativeToWindowPos;






	//member functions
public:
	Player()
	{
		playerAudio.loadAudio();
	}
	PlayerDrawables playerDrawables;
	const int			MAXLIVES = 10;
	int					currentLives = 10;
	int					selectedSkin = 1;
	Bullet				bullet[30];
	sf::RectangleShape	collisionBox;
	bool				shooting = false;
	sf::CircleShape     detectRadius;
	bool				canMove = true;
	const int			MAXAMMOPERMAG = 30;


	void                pickupAmmo(int t_amount);
	void				drawUI(sf::RenderWindow& t_window);
	sf::Sprite&			getSprite();
	sf::Vector2f		getPosition();
	void				takeDamage();
	void				heal();
	void				animate();
	void				updateText();
	void				setSkin(int t_value);
	void				setPosition(sf::Vector2f t_newPos);
	void				updateUI(sf::View t_view);
	void				initialise();
	void				draw(sf::RenderWindow& t_window);
	void				processInput();
	void				processSprintInput();
	void				processNormalMove();
	void				processFireInput();
	void				update(sf::RenderWindow& t_window);
	void				reload();
	void				refillAmmo();
	void				processDetectionRadius();

};

