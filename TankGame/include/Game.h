//Author: Filip Rusiecki													//
//Date: 10-12-2020														   //
//Description: Just a simple tank game :)								  //
//Known Bugs: Tank keeps teleporting to origin when hitting off walls.	 //
//////////////////////////////////////////////////////////////////////////
#pragma once					//include other files
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Tank.h"
#include "LevelLoader.h"
#include "Projectile.h"
#pragma comment(lib,"thor-d.lib") 
#pragma comment(lib,"thor.lib") 
#include "Thor/Time.hpp"
#include <SFML/Audio.hpp>
#include "Globals.h"
#include "MainMenu.h"
#include "TankAI.h"
#include <iostream>
#include <GameState.h>
#include <HUD.h>



class Game		//game class
{	
public:			
	LevelData m_level;			//level object
	Tank m_tank;				//tank object
	TankAi m_aiTank;
	GameState m_gameState{ GameState::GAME_RUNNING };


	sf::Vector2f m_startPoint;		//start point of the bullet
	sf::Texture m_timerTexture;		//texture for the timer
	int score;						//totalscore variable
	int randomScore;				//random score variable
	sf::SoundBuffer buffer;			//buffer for the audio
	sf::Sound sound;				//sound variable for the game
	thor::Timer m_gameTime;			//timer for the game
	static constexpr float TIMER_DURATION = 60000.0f;		//time for the game 
	float accuracy;
	float shotCounter; //counter to see how many times bullet is fired.
	float hitCounter;	//counter to see how many times bullet is hit.
	int challangeCounter; //counter for the time challange
	sf::Time m_targetTimer;			//timer for the target
	int shotCounterFunc();		//counter to count how much bullets were shot 
	bool gameAlive;			//bool to check if the game is on
	sf::Text m_accuracyText;
	sf::Text m_endGame;

	std::function<void(int)> m_funcApplyDamage;

	sf::RectangleShape m_rectShape;		//rect shape for the timer texture
	static const int TIMING_BAR_WIDTH{ 210 };		//width variable for the timer
	Game();
	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();
	void generateWalls();			//generating walls function
	void generateTargets();			//generating targets function
	bool checkWallCollision();		//checking collisions for bullets and walls 
	bool checkTargetCollision();	//checking collisions for bullets and targets
	void gameInstructions();		//void for the instructions tab
	sf::Sprite getInstructionsBg();	//function to return the sprite for the instructions tab

	sf::Font m_againstFont;			//custom font variable
	bool target1;			//bool for target 1 
	bool target2;			//bool for target 2 
	bool target3;			//bool for target 3 

	MainMenu m_mainMenu; // object used to display main menu
	int gameMode;   // to represent the different modes in the game, for  
					// example game instruction mode and game play mode

	sf::Texture m_instructionsTexture;			//texture for instructions menu
	sf::Sprite m_instructionsSprite;	//sprite for instructions menu
	sf::Text m_score;					//string variable to display score			

protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	void targetRandomRespawn();		//random respawn function for the targets
	// main window
	sf::RenderWindow m_window;


	// Player tank sprite and texture
	//sf::Sprite m_tankSprite;
	//sf::Texture m_tankTexture;

	sf::Text m_timeText;			//text that says "time"
	sf::Sprite m_bgSprite;			//background sprite
	sf::Texture m_bgTexture;		//background texture
	sf::Sprite m_hudSprite;			//sprite for the hud of the game
	sf::Texture m_hudTexture;		//texture for the hud of the game


	sf::Texture m_targetTexture;				//texture for the target
	std::vector<sf::Sprite> m_targetSprites;	//tagret vector sprites
	std::vector<sf::Sprite> m_sprites;			//wall vector sprites

	// At texture for the sprite sheet 
	sf::Texture m_spriteSheetTexture;	
	sf::Texture m_texture;
	HUD m_hud;	// The game HUD instance.
};