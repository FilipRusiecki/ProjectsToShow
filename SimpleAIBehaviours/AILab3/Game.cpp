

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "AILab3" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}


Game::~Game()
{
}



void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		myWander.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mySeek.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		myArriveFast.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		myArriveSlow.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		myFlee.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		myPursue.alive ^= true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		myPlayer.tracerAlive ^= true;
		myWander.tracerAlive ^= true;
		mySeek.tracerAlive ^= true;
		myFlee.tracerAlive ^= true;
		myArriveFast.tracerAlive ^= true;
		myArriveSlow.tracerAlive ^= true;
		myPursue.tracerAlive ^= true;

	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	//myPlayer.visPointLeft.x = myPlayer. m_playerSprite.getPosition().x + 400 * cos(myPlayer.angleInRadsLeft);
	//myPlayer.visPointLeft.y = myPlayer.m_playerSprite.getPosition().y + 400 * sin(myPlayer.angleInRadsLeft);

	//myPlayer.visPointRight.x = myPlayer.m_playerSprite.getPosition().x + 400 * cos(myPlayer.angleInRadsRight);
	//myPlayer.visPointRight.y = myPlayer.m_playerSprite.getPosition().y + 400 * sin(myPlayer.angleInRadsRight);

	/*sf::Vector2f targetDirection = { myFlee.m_fleeSprite.getPosition().x - myPlayer.m_playerSprite.getPosition().x,myFlee.m_fleeSprite.getPosition().y - myPlayer.m_playerSprite.getPosition().y };
	float dotProduct = (targetDirection.x * myPlayer.rotation) + (targetDirection.y * myPlayer.rotation);

	if (dotProduct >= 360)
	{
		dotProduct = dotProduct - 360;
	}
	std::cout << dotProduct << std::endl;
	if (dotProduct < myPlayer.angle)
	{

		sf::Vertex begin1{ myPlayer.m_playerSprite.getPosition(),sf::Color::Red };
		myPlayer.playerVisLeft.append(begin1);
		sf::Vertex end1{ myPlayer.visPointLeft, sf::Color::Red };
		myPlayer.playerVisLeft.append(end1);


		sf::Vertex begin2{ myPlayer. m_playerSprite.getPosition(),sf::Color::Red };
		myPlayer.playerVisRight.append(begin2);
		sf::Vertex end2{ myPlayer.visPointRight, sf::Color::Red };
		myPlayer.playerVisRight.append(end2);
	}
	else
	{

		sf::Vertex begin1{ myPlayer.m_playerSprite.getPosition(),sf::Color::Green };
		myPlayer.playerVisLeft.append(begin1);
		sf::Vertex end1{ myPlayer.visPointLeft, sf::Color::Cyan };
		myPlayer.playerVisLeft.append(end1);


		sf::Vertex begin2{ myPlayer.m_playerSprite.getPosition(),sf::Color::Green };
		myPlayer.playerVisRight.append(begin2);
		sf::Vertex end2{ myPlayer.visPointRight, sf::Color::Cyan };
		myPlayer.playerVisRight.append(end2);
	}*/


	myPlayer.update(t_deltaTime);
	myWander.update(t_deltaTime,myPlayer);
	mySeek.update(t_deltaTime, myPlayer);
	myFlee.update(t_deltaTime, myPlayer);
	myArriveFast.update(t_deltaTime, myPlayer);
	myArriveSlow.update(t_deltaTime, myPlayer);
	myPursue.update(t_deltaTime, myPlayer);

}


void Game::render()
{
	m_window.clear(sf::Color::Black);
	myPlayer.render(m_window);
	myWander.render(m_window);
	mySeek.render(m_window);
	myFlee.render(m_window);
	myArriveFast.render(m_window);
	myArriveSlow.render(m_window);
	myPursue.render(m_window);
	m_window.draw(info);
	//m_window.draw(myPlayer.playerVisLeft);
	//m_window.draw(myPlayer.playerVisRight);

	m_window.display();
}


void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}


}


void Game::setupSprite()
{
	info.setFont(m_font);
	info.setScale(1.0f, 1.0f);
	info.setString("Press 1: Wander , 2:Seek , 3:ArriveFast , 4: ArriveSlow , 5:Flee , 6:Pursue , 8:TracerLines \n L: player speed = 0\n K: player speed = 2\n J: player speed = 5");
	info.setPosition(10.0f, 10.0f);
}
