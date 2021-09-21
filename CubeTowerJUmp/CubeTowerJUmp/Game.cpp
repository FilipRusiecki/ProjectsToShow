#include "Game.h"
using namespace std;

Game::Game() : m_Window(sf::VideoMode(static_cast<int>(550), static_cast<int>(900)), "CubeTowerFlying", sf::Style::Default)
{
	srand(time(NULL));
	loadContent();
	myPlayer.playerConst();
	spawnPlatforms();
//	setUpSmudge();
	startGame = true;
	m_sound.play();
	m_sound.setLoop(true);
	
}

void Game::run()
{
	srand(time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	// the clock object keeps the time.
	sf::Clock clock;
	

	clock.restart();
	

	while (m_Window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
				m_Window.close();
		}
		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();
			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop
}

void Game::update()
{
	m_sound.setVolume(20.0f);
	float deltaTime = myPlayer.clock.restart().asSeconds();

	acceleration = acceleration + 0.001f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && startGame == false)
	{
		myPlayer.velocity.x = -myPlayer.speed;
		myPlayer.shape.move(myPlayer.velocity.x * deltaTime *2, 0);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && startGame == false)
	{
		myPlayer.velocity.x = myPlayer.speed;
		myPlayer.shape.move(myPlayer.velocity.x * deltaTime *2, 0);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		startGame = false;
		scoreText.setPosition(200, 30);

	}
	if (startGame == true)
	{
		scoreText.setString("Previous Best: " + std::to_string(previousScore));
		scoreText.setPosition(150, 230);	
	}
	if (startGame == false)
	{
		showScore = true;
		respawnPlatforms();
		score++;
		myPlayer.shape.move(myPlayer.velocity.x * deltaTime , 0);
		scoreText.setString("Score: " + std::to_string(score));
	}
	playerOffScreen();
	
	followPlayer();

	//followPlayer.setCenter(275, myPlayer.shape.getPosition().y -400);
	//m_Window.setView(m_Window.getDefaultView());
}

void Game::draw()
{
	m_Window.clear(sf::Color(245, 173, 17, 0));
	m_Window.draw(myPlayer.shape);
	for (int i = 0; i < 10; i++){m_Window.draw(myPlatform[i].platform);}
	m_Window.draw(playerSmudge.playerSmudge);
	if (startGame == true){m_Window.draw(startGameText);}

	m_Window.draw(scoreText);

	m_Window.display();

}

void Game::loadContent()
{
	if (!m_font.loadFromFile("./Assets/Pixellari.ttf"))
	{
		std::cout << "error loading font" << std::endl;
	}
	if (!m_buffer.loadFromFile("./Assets/Music.ogg"))
	{
		std::cout << "error loading music" << std::endl;
	}


	m_sound.setBuffer(m_buffer);
	scoreText.setFont(m_font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(200, 30);

	startGameText.setFont(m_font);
	startGameText.setString("Press Space to Start");
	startGameText.setFillColor(sf::Color::White);
	startGameText.setPosition(140, 200);
}

void Game::spawnPlatforms()
{
	int addOn = 0;
	for (int i = 0; i < 10; i++)
	{
		myPlatform[i].randomPos.x = rand() % 550 + 0;
		myPlatform[i].randomPos.y = 0 + addOn;
		myPlatform[i].platform.setPosition(myPlatform[i].randomPos.x, myPlatform[i].randomPos.y );
		addOn += 100;
	}
}

void Game::respawnPlatforms()
{
	for (int i = 0; i < 10; i++)
	{
		if (myPlatform[i].platform.getPosition().y > 900)
		{
			myPlatform[i].randomPos.x = rand() % 550 + 0;
			myPlatform[i].randomPos.y = -100;
			myPlatform[i].platform.setPosition(myPlatform[i].randomPos);
		}
		myPlatform[i].velocity.y = myPlatform[i].speed * 2 + acceleration;
		myPlatform[i].platform.move(myPlatform[i].velocity.x, myPlatform[i].velocity.y);
		if (myPlatform[i].platform.getGlobalBounds().intersects(myPlayer.shape.getGlobalBounds()))
		{
			restartGame();
		}
	}
}

void Game::playerOffScreen()
{
	sf::Vector2f playerPos = myPlayer.shape.getPosition();
	if (playerPos.x > 550 + myPlayer.size.x)
	{
		myPlayer.shape.setPosition(-myPlayer.size.x,playerPos.y);
	}
	if (playerPos.x < 0 - myPlayer.size.x)
	{
		myPlayer.shape.setPosition( 550, playerPos.y);
	}
}

void Game::restartGame()
{
	startGame = true;
	spawnPlatforms();
	myPlayer.shape.setPosition(275, 850.0 - myPlayer.size.y);
	acceleration = 0.01f;
	if(previousScore < score){previousScore = score;}
	score = 0;
	myPlayer.velocity.x = 0;
}

void Game::setUpSmudge()
{

		playerSmudge.playerSmudge.setPosition(myPlayer.shape.getPosition().x, myPlayer.shape.getPosition().y);


}

void Game::followPlayer()
{
	
	sf::Vector2f playerPos;
	playerPos = myPlayer.shape.getPosition();

	int number = 1;
	int addOn = 0;




	if (allowRespawn == true)
	{
		playerSmudge.playerSmudge.setPosition(playerPos.x + 4, playerPos.y );
		playerSmudge.velocity.y = playerSmudge.speed * 2;
		allowRespawn = false;
	}
	if (allowRespawn == false)
	{
		playerSmudge.playerSmudge.move(0, playerSmudge.velocity.y);

		if (playerSmudge.playerSmudge.getPosition().y > 900)
		{
			allowRespawn = true;
		}

	}




}





