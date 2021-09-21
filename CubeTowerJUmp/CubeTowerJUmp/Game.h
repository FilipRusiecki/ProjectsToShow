#pragma once

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else #pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif #include "ScreenSize.h"
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "Platform.h"
#include "smudge.h"

class Game
{
	sf::RenderWindow m_Window;
	
public:
	Game();
	void	run();
	void	update();
	void	draw();
	void	loadContent();

private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	//sf::View followPlayer; 
	sf::Text scoreText;
	sf::Text startGameText;
	sf::Font m_font;
	player myPlayer;
	Platform myPlatform[10];
	bool platformRespawn[10];
	Smudge playerSmudge;

	bool startGame;
	bool showScore = false;
	int score = 0;
	int previousScore= 0;
	float acceleration = 0.01f;
	void	spawnPlatforms();
	void	respawnPlatforms();
	void	playerOffScreen();
	void	restartGame();

	void setUpSmudge();
	void followPlayer();
	bool doloop = true;
	bool allowRespawn = true;
	bool allowRespawnTwo = true;
	bool allowRespawnTree = true;

};
