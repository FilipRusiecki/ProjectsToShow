#include "Game.h"


Game::Game()
	: m_window{ sf::VideoMode{1920, 1080}, "SMFL Game",  } 
{
	srand(time(NULL));
	zombieResources.loadZombieTexture();
	zombieResources.loadZombieSound();
	gameMode = 1;
	m_window.setKeyRepeatEnabled(false);
	setupMenu();
	setupLevel(amountZombies);
	worldGrid.setupGrid(basicWall);
	sf::Listener::setDirection(0.f, 1.f, 0.f);

}

void Game::setupMenu()
{
	
	


	if (!m_ariblkFont.loadFromFile("ART/FONTS/ariblk.ttf"))
	{
		std::cout << "error with font file ";
	}
	if (!m_againstFont.loadFromFile("ART/FONTS/rough.otf"))
	{
		std::cout << "error with font file ";
	}
	if (!m_pressToStartTexture.loadFromFile("ART/MENU/pressToStart.gif"))
	{
		std::cout << "error with image file ";
	}

	if (!m_menuBgTexture.loadFromFile("ART/MENU/bg.jpg"))
	{
		std::cout << "error with image file ";
	}

	if (!bgMusicBuffer.loadFromFile("MUSIC/bg.ogg"))
	{
		std::cout << "error with sound file";
	}
	if (!roundChangeBuffer.loadFromFile("MUSIC/roundChange.ogg"))
	{
		std::cout << "error with sound file";
	}
	roundChangeSound.setBuffer(roundChangeBuffer);
	bgMusic.setBuffer(bgMusicBuffer);
	m_menuBgSprite.setTexture(m_menuBgTexture);
	m_menuBgSprite.setScale(1.0f, 1.0f);
	m_mainMenu.initialise(m_againstFont);		//passing custom font for the menu buttons
	myInstructions.init();
	myCharacterCustiomization.init();
	mySettings.init();
	bgMusic.play();
}

void Game::setupLevel(int t_amountZombies)
{

	//clears vector of zombies to avoid leaks when recreating levels;
	
	for (auto z : zombie)
	{
		delete z;
	}
	for (auto w : basicWall)
	{
		delete w;
	}
	zombie.clear();

	amountZombies = t_amountZombies;

	consumable[0] = new Medkit(0.5, "medkit.png", sf::Vector2f(1200, 600), "GotBandages.wav");
	consumable[1] = new Ammocrate(0.15, "ammocrate.png", sf::Vector2f(110, 1200),"LockedLoaded.wav");


	basicWall.push_back(new Wall(sf::Vector2f(0, 2050), 10, 4100));//left wall
	basicWall.push_back(new Wall(sf::Vector2f(2050, 0), 4100, 10));//top wall
	basicWall.push_back(new Wall(sf::Vector2f(4100, 2050), 10, 4100));//right wall
	basicWall.push_back(new Wall(sf::Vector2f(2050, 4100), 4100, 10));//bottom wall
	//set outer walls to true
	for (auto w : basicWall)
	{
		w->isOuter = true;
	}


	basicWall.push_back(new Wall(sf::Vector2f(60, 900), 300, 150));//car on the very left + barrels
	basicWall.push_back(new Wall(sf::Vector2f(1300, 1500), 400, 200));//heli 
	basicWall.push_back(new Wall(sf::Vector2f(500, 1100), 200, 210)); //crates near the car on left 
	basicWall.push_back(new Wall(sf::Vector2f(610, 1930), 450, 200));// container1
	basicWall.push_back(new Wall(sf::Vector2f(610, 2420), 450, 200));// container2
	basicWall.push_back(new Wall(sf::Vector2f(610, 3000), 450, 200));// container3
	basicWall.push_back(new Wall(sf::Vector2f(510, 3600), 770, 600));//building 1
	basicWall.push_back(new Wall(sf::Vector2f(1610, 3600), 770, 600));//building 2
	basicWall.push_back(new Wall(sf::Vector2f(1250, 2130), 450, 460));// container2
	basicWall.push_back(new Wall(sf::Vector2f(1860, 2390), 50, 50));// cross
	basicWall.push_back(new Wall(sf::Vector2f(1600, 880), 270, 150));//APC 1
	basicWall.push_back(new Wall(sf::Vector2f(2150, 880), 270, 150));//cars beside apc
	basicWall.push_back(new Wall(sf::Vector2f(3950, 880), 270, 150));//apc 2 at the right
	basicWall.push_back(new Wall(sf::Vector2f(3100, 320), 330, 320));//top right
	basicWall.push_back(new Wall(sf::Vector2f(2930, 520), 10, 180));//wall of top right
	basicWall.push_back(new Wall(sf::Vector2f(3420, 600), 930, 10));//wall2 of top right
	basicWall.push_back(new Wall(sf::Vector2f(3570, 210), 330, 180));//top right
	basicWall.push_back(new Wall(sf::Vector2f(3160, 1550), 140, 300));//truck
	basicWall.push_back(new Wall(sf::Vector2f(3590, 1490), 580, 600));//building beside truck
	basicWall.push_back(new Wall(sf::Vector2f(3550, 2900), 610, 600));//building bottom left
	basicWall.push_back(new Wall(sf::Vector2f(2700, 2050), 200, 150));//cars on round about 1
	basicWall.push_back(new Wall(sf::Vector2f(2400, 2900), 200, 200));//cars on round about 2
	basicWall.push_back(new Wall(sf::Vector2f(3370, 3730), 150, 220));//apc at the bottom
	basicWall.push_back(new Wall(sf::Vector2f(4000, 3800), 250, 220));//cars on the bottom right
	basicWall.push_back(new Wall(sf::Vector2f(3500, 2280), 10, 520));//shop left wall 
	basicWall.push_back(new Wall(sf::Vector2f(3200, 2010), 600, 10));//shop top wall 
	basicWall.push_back(new Wall(sf::Vector2f(3200, 2550), 600, 10));//shop bottom wall 
	basicWall.push_back(new Wall(sf::Vector2f(2900, 2500), 10, 80));//shop right wall 
	basicWall.push_back(new Wall(sf::Vector2f(2900, 2100), 10, 180));//shop right wall 






	m_window.setFramerateLimit(144);
	m_window.setMouseCursorVisible(false);
	player.initialise();

	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	view.setCenter(player.getPosition());
	for (int i = 0; i < 3; i++)
	{
		
		if (!backgroundtexture[i].loadFromFile("ART/backgroundLayer"+  std::to_string(i)  +  ".png"))
		{
			//error;
		}
		backgroundtexture[i].setSmooth(true);
		background[i].setTexture(backgroundtexture[i]);
		background[i].setScale(2, 2);
		background[i].setPosition(0, 0);
		
	}
	
	
	player.setPosition(sf::Vector2f(0, 0));
	view.setCenter(player.getPosition());

	for (int i = 0; i < amountZombies; i++)
	{

		zombie.push_back(new Zombie);
		zombie[i]->init(zombieResources);
	}




	m_window.setMouseCursorGrabbed(false);
	weather.init();

	player.setPosition(sf::Vector2f(1000, 500));

	for (auto w :basicWall)
	{
		w->lastKnownPlayerPos = player.getPosition();
	}


}

	

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{		
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);			
		}
		render();
	}
}

void Game::processCollisions()
{
	for (auto z: zombie)
	{
	

		for (int j = 0; j < 30; j++)
		{
			if (player.bullet[j].bulletState == Bullet::State::moving)
			{
				if (player.bullet[j].bulletBody.getGlobalBounds().intersects(z->collisionBox.getGlobalBounds()) &&
					z->alive)
				{
					z->alive = false;
					
					currentZombies--;
					zombiesKilled++;
					
				
				}
			}
		}






		if (z->zombieProjectile.bulletState == Bullet::State::moving)
		{
			if (z->zombieProjectile.bulletBody.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds()))
			{
				player.takeDamage();
				
				z->stopProjectile();
			}
		}
	}


	for (auto w : basicWall)
	{
		w->checkCollisionsWithPlayer(player);
		for (auto z : zombie)
		{



			w->checkCollisionsWithEnemy(*z);
		}
	}


}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();

		}
		
	}
}

void Game::update(sf::Time)
{

	

	audioListener.setPosition(player.getPosition().x,player.getPosition().y,0);
	audioListener.setGlobalVolume(10);

	debug = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		debug = true;
		worldGrid.at(17).cellBody.setFillColor(sf::Color::Blue);
		
	}

	if (gameMode == CHARACTER_CUSTOMIZATION)
	{
		myCharacterCustiomization.update();
		myCharacterCustiomization.draw(m_window);
		player.playerDrawables.selectedSkin = myCharacterCustiomization.selectedSkin;
	}

	if (gameMode == MENU)
	{
		m_window.setMouseCursorVisible(true);
		m_mainMenu.update(m_window, gameMode);
		
	}
	else if (gameMode == CONTROLS)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameMode = MENU;
		}
	}
	else if (gameMode == PLAY)
	{
		if (zombieSpawnTimer.getElapsedTime() > sf::seconds(5) && zombieSpawnCounter < newAmountOfZombies)
		{


			zombieSpawnCounter += 1;
			Zombie* tempZombie = new Zombie;
			tempZombie->init(zombieResources);
			int zombieSpot1 = rand() % 100;
			

			tempZombie->setPosition(worldGrid.at(zombieSpot1).cellBody.getPosition() + sf::Vector2f(204.6,204.6));

			zombie.push_back(tempZombie);
			std::cout << "spawned zombie" << std::endl;
			zombieSpawnTimer.restart();

			

		}


		for (auto z : zombie)
		{
			z->update(player.getPosition(), player.detectRadius.getRadius(), player.collisionBox, player.currentLives, worldGrid, worldGrid.getCellPlayerIsIn(player.getPosition()));
			z->getCell(worldGrid);
		}



		bgMusic.pause();
		m_window.setMouseCursorVisible(false);
	


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		{
			Game::setupLevel(5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			Zombie* tempZombie = new Zombie;
			tempZombie->init(zombieResources);
			tempZombie->setPosition(sf::Vector2f(30, 30));

			zombie.push_back(tempZombie);
			std::cout << "spawned zombie" << std::endl;


		}

		if (roundCounter == 0)
		{
			if (zombiesKilled == 5 && round_timer == false)
			{
				timeBetweenRoundsTimer.restart();
				round_timer = true;
				std::cout << "all zombies killed" << std::endl;
				
				
			}
		}
		else
		{
			if (zombiesKilled == newAmountOfZombies && round_timer == false)
			{
				timeBetweenRoundsTimer.restart();
				round_timer = true;
				std::cout << "Round:" << roundCounter << std::endl;

			}
		}


		if (round_timer == true)
		{
			
			if (timeBetweenRoundsTimer.getElapsedTime() > sf::seconds(5))
			{
				roundChange();
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{

			view.zoom(1.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{

			view.zoom(0.8);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{

			m_window.close();
		}




		checkGameOver();
		processCollisions();
		checkPickup();
		player.processInput();
		player.update(m_window);
		player.updateUI(view);

		

		//10 walls for collision
		
		weather.update(m_window);
	}
	else if (gameMode == SETTINGS)
	{
	
		mySettings.update();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameMode = MENU;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			audioListener.setGlobalVolume(0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			audioListener.setGlobalVolume(10);
		}

	}
	else if (gameMode == PRESS_TO_START)
	{

	}
	else if (gameMode == CHARACTER_CUSTOMIZATION)
	{
		myCharacterCustiomization.update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameMode = MENU;
		}
	}


}

void Game::render()
{

	m_window.clear();
	


	if (gameMode == MENU)
	{
		m_window.setMouseCursorVisible(true);
		m_window.draw(m_menuBgSprite);
		m_mainMenu.draw(m_window);
		

	}
	else if (gameMode == CONTROLS)
	{
		myInstructions.draw(m_window);

	}
	else if (gameMode == SETTINGS)
	{
		mySettings.draw(m_window);
	}
	else if (gameMode == PLAY)
	{
		view.setRotation(0);


		//	if (player.getPosition().x - 500 > 0 && player.getPosition().x + 500 < 1920 )
		{
			view.setCenter(player.getPosition().x, view.getCenter().y);
		}

		//	if (player.getPosition().y > 0 && player.getPosition().y < 1752)
		{
			view.setCenter(view.getCenter().x, player.getPosition().y);
		}


		if (player.shooting)
		{
			view.setRotation(rand() % 5);
			view.setCenter(sf::Vector2f(player.getPosition().x, view.getCenter().y) + sf::Vector2f(rand() % 15, rand() % 15));
		}


		m_window.clear();
		//m_window.draw(background[0]);


		for (int i = 0; i < 2; i++)
		{
			consumable[i]->draw(m_window);
		}

	
		m_window.setView(view);
		player.draw(m_window);
		for (auto z :zombie)
		{
			z->draw(m_window);
		}
		weather.draw(m_window);


		
		m_window.draw(background[2]);
		m_window.draw(background[1]);
		if (debug)
		{
			for (auto w : basicWall)
			{
				w->draw(m_window);
			}
		}

		m_window.draw(player.playerDrawables.damageSprite);

		player.drawUI(m_window);
	}




	else if(gameMode == CHARACTER_CUSTOMIZATION)
	{
		myCharacterCustiomization.draw(m_window);
	}




	if (debug)
	{
		worldGrid.draw(m_window);
		for (auto z : zombie)
		{
			m_window.draw(z->zombieText);
		}
	}



	m_window.display();
	
}

void Game::checkPickup()
{
	if (player.getSprite().getGlobalBounds().intersects(((Medkit*)consumable[0])->consumableSprite.getGlobalBounds() )
		&& ((Medkit*)consumable[0])->active == true && player.currentLives < player.MAXLIVES)
	{
		((Medkit*)consumable[0])->pickup(player);
		
		
	}

	if (player.getSprite().getGlobalBounds().intersects(((Ammocrate*)consumable[1])->consumableSprite.getGlobalBounds())
		&& ((Ammocrate*)consumable[1])->active == true )
	{
		((Ammocrate*)consumable[1])->pickup(player);
		
	}
}

void Game::checkGameOver()
{
	if (player.currentLives <= 0)
	{
		m_window.close();
	}


	
}

void Game::spawnConsumables()
{
	for (int i = 0; i < 2; i++)
	{
		consumable[i]->active = true;
		consumable[i]->position = sf::Vector2f(500 * i, 500 * i);
	}
}

void Game::roundChange()
{
	roundChangeSound.play();
	roundCounter++;
	newAmountOfZombies = newAmountOfZombies + 3;
	zombieSpawnCounter = 0;
	zombiesKilled = 0;
	round_timer = false;

}



