#ifndef GAME
#define GAME


#include "resourceHolder.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "VectorAlgebra2D.h"
#include "Medkit.h"
#include "Ammocrate.h"
#include "Weather.h"
#include "Zombie.h"
#include "Wall.h"
#include "Thor/Graphics.hpp"
#include "Grid.h"



#include "Globals.h"
#include "MainMenu.h"
#include "Instructions.h"
#include "CharacterCustomization.h"
#include "Settings.h"
#include "SFML/Audio.hpp"



class Game
{
public:
	Game();
	void run();
	void			 setupMenu();
	void			 setupLevel(int t_amountZombies);
	void			 processCollisions();
	void             processEvents();
	void             update(sf::Time);
	void             render();
	void             checkPickup();
	void			 checkGameOver();
	void			 spawnConsumables();
	void             setCharacterSkin();
	void             roundChange();
	sf::SoundBuffer	 roundChangeBuffer;
	sf::Sound		 roundChangeSound;
	bool             round_timer = false;
private:
	sf::Clock timeBetweenRoundsTimer;
	sf::Clock consumableSpawnClock;
	sf::Listener audioListener;
	int amountZombies = 1;
	Player player;
	resourceHolder zombieResources;
	std::vector<Zombie*> zombie;
	Consumable* consumable[2];
	std::vector<Wall*> basicWall;
	int currentZombies = amountZombies;
	instructions myInstructions;
	CharacterCustomization myCharacterCustiomization;
	Settings mySettings;



	bool debug = false;


	Grid worldGrid;
	sf::Font m_ariblkFont;	    //font
	sf::Font m_againstFont;				//font
	MainMenu m_mainMenu;				// object used to display main menu
	sf::Text m_message; 				//  message string for instructions
	sf::Text m_message2;				//	second message in instructions tab

	int gameMode;						// to represent the different modes in the game, for  
										// example game instruction mode and game play mode

	sf::Texture m_instructionsBg;		//instruction background texture
	sf::Sprite m_instructionsBgSprite;	//instruction background sprite(will have seperate class soon)
	sf::Texture m_buttonTexture;		//button texture
	sf::Sprite m_pressToStartSprite;	//sprite for press to start
	sf::Texture m_pressToStartTexture;	//spress to start texture
	sf::Sprite m_menuBgSprite;
	sf::Texture m_menuBgTexture;


	sf::SoundBuffer bgMusicBuffer;
	sf::Sound bgMusic;
	
	sf::Clock zombieSpawnTimer;




	int                roundCounter = 0;
	int                zombieSpawnCounter = 0;
	int                newAmountOfZombies = 5;
	int                zombiesKilled = 0;


	
	sf::Vector2f     viewMove{ 0,0 };
	sf::Sprite       background[3];
	sf::Texture      backgroundtexture[3];
	Weather          weather;
private:
	
	sf::RenderWindow m_window;
	sf::View view;
};

#endif // !GAME
