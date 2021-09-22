//Author: Filip Rusiecki													//
//Date: 10-12-2020														   //
//Description: Just a simple tank game :)								  //
//Known Bugs: bullets shot has a problem counts them in two's :(		 //
//////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include <iostream>
#include <Thor/Vectors.hpp>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;
//bullet myBullet;



int Game::shotCounterFunc()
{
	return shotCounter += 1;
}

////////////////////////////////////////////////////////////
Game::Game()
: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "TankShooter", sf::Style::Default)
, m_tank(m_texture, m_sprites)//, sf::Vector2f(700, 700))
, m_aiTank(m_texture, m_sprites)
, m_hud(m_againstFont) // Add this line
{
	
	srand(time(nullptr));				//srand to randomize random numbers
	randomScore = rand() % 15 + 10;		//creating random score
	gameMode = 1;						//setting the gamemode to menu
	gameAlive = true;					 ///bool to set game alive
	m_window.setKeyRepeatEnabled(false);		//do single event when key is pressed
	//myBullet.bulletConst();						//bullet constructor 
	m_window.setVerticalSyncEnabled(true);
	shotCounter = 0;			//shoot counter
	hitCounter = 0;				//hit counter
	accuracy = 0;				//accuracy counter
	int currentLevel = 1;	


	//will Generate an exception if level loading fails ***************
	try
	{
		LevelLoader::load(currentLevel, m_level);		//loading in the level
	}
	catch (std::exception& e)
	{
		std::cout << "Level loading failure " << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	if (!m_texture.loadFromFile("./resources/images/SpriteSheet2.png"))				//loading the texutre for the tank, if not loaded it shows error
	{
		std::string s("Error loading texture");								
		throw std::exception(s.c_str());
	}
		
	if (!m_bgTexture.loadFromFile("./resources/images/sand.png"))					//loading the texutre for the background, if not loaded it shows error
	{
		std::string s("Error loading the texture");
		throw std::exception(s.c_str());
	}
	m_bgSprite.setTexture(m_bgTexture);												//setting the background texture of the sprite 

	if (!m_spriteSheetTexture.loadFromFile("./resources/images/SpriteSheet.png"))	//loading the texutre for the tank, if not loaded it shows error
	{
		std::string errorMsg("Error loading texture");
		throw std::exception(errorMsg.c_str());
	}
	if (!m_timerTexture.loadFromFile("./resources/images/timerbar.png"))			//loading the texutre for the timerbar, if not loaded it shows error
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	if (!buffer.loadFromFile("./resources/audio/shootEffect.wav"))					//loading the sound for the bullet, if not loaded it shows error
	{
		std::string s("Error loading audio");
		throw std::exception(s.c_str());
	}
	if (!m_hudTexture.loadFromFile("./resources/images/hud2.png"))					//loading the sound for the bullet, if not loaded it shows error
	{
		std::string s("Error loading hud Texture");
		throw std::exception(s.c_str());
	}
	if (!m_againstFont.loadFromFile("./resources/fonts/againstItalic.ttf"))			//loading the font, if not loaded it shows error
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}

	if (!m_targetTexture.loadFromFile("./resources/images/target1.png"))		//loading the texture for the target, if not loaded it shows error
	{
		std::cout << "Error... Loading target texture" << std::endl;
		
	}

	if (!m_instructionsTexture.loadFromFile("./resources/images/keyboard.png"))		//loading the texture for the instructions menu, if not loaded it shows error
	{
		std::cout << "Error... Loading target texture" << std::endl;
		
	}

	//properties for the instructions sprite
	m_instructionsSprite.setTexture(m_instructionsTexture);
	m_instructionsSprite.setPosition(400, 50);

	//properties for the score text
	m_score.setFillColor(sf::Color::Black);
	m_score.setFont(m_againstFont);
	m_score.setPosition(6, 70);

	//properties for the time string
	m_timeText.setString("Time:");
	m_timeText.setFont(m_againstFont);
	m_timeText.setFillColor(sf::Color::White);
	m_timeText.setPosition(0, 13);

	//properties of accuracy text
	m_accuracyText.setString("Accuracy: ");
	m_accuracyText.setFont(m_againstFont);
	m_accuracyText.setFillColor(sf::Color::Black);
	m_accuracyText.setPosition(600, 100);

	//properties of endgame text
	m_endGame.setString("Press Escape to go to main menu ");
	m_endGame.setFont(m_againstFont);
	m_endGame.setFillColor(sf::Color::Black);
	m_endGame.setPosition(600, 300);

	//properties for the hud
	m_hudSprite.setTexture(m_hudTexture);
	m_hudSprite.setPosition(0, 0);

	//properties for the sound variable
	sound.setBuffer(buffer);

	//properties for the timer bar
	m_rectShape.setSize(sf::Vector2f(TIMING_BAR_WIDTH, 35));
	m_rectShape.setPosition(75, 15);
	m_rectShape.setTexture(&m_timerTexture);
	
	//reseting the game timer
	m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));

	//setting the timer of the target
	m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);


	// Extract the wall image from the spritesheet.
	sf::Sprite sprite;
	sf::IntRect wallRect(2, 129, 33, 23);
	sprite.setTexture(m_spriteSheetTexture);
	sprite.setTextureRect(wallRect);

	//start the timer for the game

	


	generateWalls();	//function to generate walls 
	generateTargets();	//function to generate targets

	m_mainMenu.initialise(m_againstFont); //passing the font to the menu
	
	target1 = true;	//setting target 1 alive
	target2 = false;//setting target 2 dead
	target3 = false;//setting target 3 dead

	m_aiTank.init(m_level.m_aiTank.m_position);

	// Point at TankAI::applyDamage()...this function expects 1 argument (damage amount), but that argument
	//  will be supplied later when we call the function inside Projectile::udpate()
	// So we use what is called a placeholder argument and this will be substituted later with the damage amount
	using std::placeholders::_1;
	// The parameters of bind are the function to be called, followed by the name of the target instance, 
	//  followed by the placeholder argument.
	m_funcApplyDamage = std::bind(&TankAi::applyDamage, &m_aiTank, _1);



}
////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
}
void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);		
	// Create the Walls 
	for (ObstacleData const& obstacle : m_level.m_obstacles)		//loop to go through all the walls 
	{
		sf::Sprite sprite;					//setting properties for all the walls 
		sprite.setTexture(m_texture);		
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}
}
void Game::generateTargets()				//loop to go through all the targets								
{
	for (TargetData const& targets : m_level.m_targets)
	{
		sf::Sprite spriteTarget;					//setting properties for all the targets 
		spriteTarget.setTexture(m_targetTexture);
		spriteTarget.setOrigin(25, 25);
		spriteTarget.setPosition(targets.m_targetPos);
		m_targetSprites.push_back(spriteTarget);
	}
}
bool Game::checkWallCollision()					//check wall collision with the bullet
{
	for (sf::Sprite const& sprite : m_sprites)					//for loop to cycle through the walls 			
	{
		//if (CollisionDetector::collision(myBullet.m_bulletSprite, sprite))
		//{
		//	if (myBullet.fired == true)			//if bullet is fired
		//	{
		//		myBullet.fired = false;			//set it to not fired after fireing 
		//		myBullet.alive = false;			//if hit something its not alive anymore
		//		myBullet.allowToFire = true;	//allowing to fire again
		//	}
		//}
	}
	return false;
}
bool Game::checkTargetCollision()				//check target collision with the bullet
{
	for (sf::Sprite const& targets : m_targetSprites)								//for loop to cycle through the targets 		
	{

		//if (target1 == true)															//setting true bool for the target 
		//{
		//	//if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(0)))		//checking for the collision between the target and the bullet
		//	//{
		//		challangeCounter = challangeCounter + 1;
		//		std::cout << "CHALLANGE COUNTER: " << challangeCounter << std::endl;

		//		//if (myBullet.fired == true)			//setting fired bool to true
		//		//{
		//		//	myBullet.fired = false;			//setting bool to false
		//		//	myBullet.alive = false;			//setting bool to false
		//		//	myBullet.allowToFire = true;	//allowing the player to shoot again
		//			score = score + randomScore;	//giving the player a random score
		//			std::cout << "score is:  " << score << std::endl;	//displaying the score in the console ================================= get rid of this later
		//		//	m_targetSprites.at(0).setPosition(10000, 10000);	//setting the target off the screen 
		//			target1 = false;	//turning off the target so it will be not drawn off the screen
		//			target2 = true;		//turning on the second target.
		//			m_targetTimer = m_targetTimer+ sf::milliseconds(m_level.m_tank.m_duration);
		//			m_targetSprites.at(1).setColor(sf::Color::White);
		//			hitCounter = hitCounter + 1;
		//			std::cout << "shots hit: " << hitCounter << std::endl;
		//		//}
		//	//}
		//}
		//if (target2 == true)															//setting true bool for the target 
		//{
		//	//if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(1)))		//checking for the collision between the target and the bullet
		//	//{
		//	//	challangeCounter = challangeCounter + 1;
		//	//	std::cout << "CHALLANGE COUNTER: " << challangeCounter << std::endl;
		//	//	if (myBullet.fired == true)			//setting fired bool to true
		//	//	{
		//	//		myBullet.fired = false;			//setting bool to false
		//	//		myBullet.alive = false;			//setting bool to false
		//	//		myBullet.allowToFire = true;	//allowing the player to shoot again
		//			score = score + randomScore;	//giving the player a random score
		//			std::cout << "score is:  " << score << std::endl;	//displaying the score in the console ================================= get rid of this later
		//			//m_targetSprites.at(1).setPosition(10000, 10000);	//setting the target off the screen 
		//			target2 = false;	//turning off the target so it will be not drawn off the screen
		//			target3 = true;		//turning on the second target.
		//			m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
		//			m_targetSprites.at(2).setColor(sf::Color::White);
		//			hitCounter = hitCounter + 1;
		//			std::cout << "shots hit: " << hitCounter << std::endl;
		//		//}
		//	//}
		//}
		//if (target3 == true)															//setting true bool for the target 
		//{
		//	//if (CollisionDetector::collision(myBullet.m_bulletSprite, m_targetSprites.at(2)))		//checking for the collision between the target and the bullet
		//	//{
		//	//	challangeCounter = challangeCounter + 1;
		//	//	std::cout << "CHALLANGE COUNTER: " << challangeCounter << std::endl;
		//	//	if (myBullet.fired == true)			//setting fired bool to true
		//	//	{
		//	//		myBullet.fired = false;			//setting bool to false
		//	//		myBullet.alive = false;			//setting bool to false
		//	//		myBullet.allowToFire = true;	//allowing the player to shoot again
		//			score = score + randomScore;	//giving the player a random score
		//			std::cout << "score is:  " << score << std::endl;	//displaying the score in the console ================================= get rid of this later
		//		//	m_targetSprites.at(2).setPosition(10000, 10000);	//setting the target off the screen 
		//			target3 = false;	//turning off the target so it will be not drawn off the screen
		//			target1 = true;		//turning on the second target.
		//			m_targetTimer = m_targetTimer + sf::milliseconds(m_level.m_tank.m_duration);
		//			m_targetSprites.at(0).setColor(sf::Color::White);
		//			hitCounter = hitCounter + 1;
		//			std::cout << "shots hit: " << hitCounter << std::endl;
		//		}
			//}
		//}

	}
	return false;

}
////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}

}
////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			gameMode = MENU;
			gameAlive = true;
			m_score.setPosition(6, 70);
			accuracy = 0;
			shotCounter = 0;
			hitCounter = 0;
		//	m_window.close();
			break;
		default:
			break;
		}
	}
}
void Game::targetRandomRespawn()	//function to randomly respawn the target after the timer goes to 0 
{
	float posX = rand() % 700 + 100;		//random x pos
	float posY = rand() % 700 + 50;			//random y pos
	sf::FloatRect m_targetRect;
	m_targetRect = m_targetSprites.at(0).getGlobalBounds();

	for (int i = 0; i > m_sprites.size();i++)
	{
		if (m_sprites.at(i).getGlobalBounds().intersects(m_targetRect))
		{
			posX = posX + 25;
			posY = posY + 25;
		}
	}

	//setting the random pos for each target if specific bools are enabled
	if (target1 == true)	
	{
		m_targetSprites.at(0).setPosition(posX, posY);
	}
	if (target2 == true)
	{
		m_targetSprites.at(1).setPosition(posX, posY);
	}
	if (target3 == true)
	{
		m_targetSprites.at(2).setPosition(posX, posY);
	}

	//setting the target colours to white
	m_targetSprites.at(0).setColor(sf::Color::White);
	m_targetSprites.at(1).setColor(sf::Color::White);
	m_targetSprites.at(2).setColor(sf::Color::White);

	//reseting the target timer
	m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);
}
////////////////////////////////////////////////////////////
void Game::update(double dt)
{ 
	
	m_score.setString("score: " + std::to_string(score));
	m_accuracyText.setString("Accuracy: " + std::to_string(static_cast<int>(accuracy)));


	switch (m_gameState)
	{
	case GameState::GAME_RUNNING:
		gameMode = GAME_PLAY;
		m_tank.update(dt, m_tank.getPosition(), m_funcApplyDamage, m_aiTank.getTankBase());
		m_aiTank.update(m_tank, dt);
		m_aiTank.collidesWithPlayer(m_tank);
		
		break;

	case GameState::GAME_WIN:
		break;

	case GameState::GAME_LOSE:
		gameAlive = true;
		m_score.setPosition(6, 70);
		accuracy = 0;
		shotCounter = 0;
		hitCounter = 0;
		m_gameState = GameState::GAME_RUNNING;
		break;

	default:
		std::cout << "Error occured" << std::endl;
		break;
	}

	if (gameMode == MENU)
	{
		m_mainMenu.update(m_window, gameMode);
		score = 0;																//reset game score when in menu
		m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));			//reset game time when in menu
		m_targetTimer = sf::milliseconds(m_level.m_tank.m_duration);			//reset target time when in menu
	}
	else if (gameMode == INSTRUCTIONS)
	{
		gameInstructions();			//function call when in instructions tab
	}
	else if (gameMode == GAME_PLAY)		//when in game loop update this 
	{
		
		if (gameAlive == true)
		{
			if (challangeCounter == 4 && m_gameTime.getRemainingTime().asMilliseconds() >= 45000.0f)		//if 4 targets are shot in 15 seconds game is finished early 
			{
				gameAlive = false;
			}
			m_aiTank.update(m_tank,dt);
			m_gameTime.start();					//start the timer
			checkWallCollision();				//check the wall collisions
			checkTargetCollision();				//check the target collisions
			

			/*if (myBullet.allowToFire == true)
			{*/
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
				/*	myBullet.allowToFire = false;
					myBullet.alive = true;
					myBullet.fired = true;*/
					
					sound.play();
					std::cout << "Shots fired " << shotCounterFunc() << std::endl;
					accuracy = hitCounter / shotCounter * 100;
					std::cout << "accuracy: " << accuracy << std::endl;
				}
				m_hud.update(m_gameState);
			//}


		/*	if (myBullet.m_bulletSprite.getPosition().x < 0 || myBullet.m_bulletSprite.getPosition().x > ScreenSize::s_width
				|| myBullet.m_bulletSprite.getPosition().y < 0 || myBullet.m_bulletSprite.getPosition().y > ScreenSize::s_height)
			{
				myBullet.allowToFire = true;
			}*/
			m_tank.update(dt, m_level.m_tank.m_position, m_funcApplyDamage, m_aiTank.getTankBase());

			if (m_aiTank.collidesWithPlayer(m_tank) == true)
			{
				m_gameState = GameState::GAME_LOSE;
			}
			/*if (myBullet.alive == true)
			{
				double rotation = m_tank.getTurretRotation();
				sf::Vector2f posTurret = m_tank.getTurretPos();

				m_startPoint = sf::Vector2f(posTurret.x + 1 * std::cos(rotation * MathUtility::DEG_TO_RAD),
					posTurret.y + 1 * std::sin(rotation * MathUtility::DEG_TO_RAD)
					);

				myBullet.m_bulletSprite.setPosition(m_startPoint);
				m_startPoint = thor::unitVector(m_startPoint - m_tank.getTurretPos());
				myBullet.alive = false;*/

			//}

		/*	myBullet.m_bulletSprite.move(m_startPoint.x * myBullet.PROJECTILE_SPEED * (dt / 1000),
				m_startPoint.y * myBullet.PROJECTILE_SPEED * (dt / 1000));*/



			if (m_gameTime.isExpired())
			{
				std::cout << "timer end " << std::endl;
				m_gameState = GameState::GAME_LOSE;
				m_hud.update(GameState::GAME_LOSE);
				gameAlive = false;	 
				if (gameAlive == false)
				{	
					render();
					for (int timer = 0; timer < 500; timer++)
					{
						std::cout << "STATE : WAITING TO RESET " << std::endl;
					}
					m_score.setPosition(6, 70);
					accuracy = 0;
					shotCounter = 0;
					hitCounter = 0;
					m_gameTime.reset(sf::Time(sf::milliseconds(TIMER_DURATION)));			//reset game time when in menu
					gameAlive = true;
					m_gameState = GameState::GAME_RUNNING;
					m_hud.update(GameState::GAME_RUNNING);
				}
			}

		

			else if (m_gameTime.isRunning())
			{
				float timerRemainPercent = m_gameTime.getRemainingTime().asMilliseconds() / TIMER_DURATION;
				m_rectShape.setScale(timerRemainPercent, 1);
				m_rectShape.setTextureRect(
					sf::IntRect(0, 0, m_timerTexture.getSize().x * timerRemainPercent,
						m_timerTexture.getSize().y));
			}
			m_targetTimer = m_targetTimer - sf::milliseconds(10);

			if (m_targetTimer < sf::milliseconds(2000))
			{
				m_targetSprites.at(0).setColor(sf::Color::Yellow);
				m_targetSprites.at(1).setColor(sf::Color::Yellow);
				m_targetSprites.at(2).setColor(sf::Color::Yellow);

			}
			if (m_targetTimer < sf::milliseconds(1000))
			{
				m_targetSprites.at(0).setColor(sf::Color::Red);
				m_targetSprites.at(1).setColor(sf::Color::Red);
				m_targetSprites.at(2).setColor(sf::Color::Red);
			}

			if (target1 == true)
			{
				if (m_targetTimer < sf::milliseconds(0))
				{
					targetRandomRespawn();
				}
			}
			if (target2 == true)
			{
				if (m_targetTimer < sf::milliseconds(0))
				{
					targetRandomRespawn();

				}
			}
			if (target3 == true)
			{
				if (m_targetTimer < sf::milliseconds(0))
				{
					targetRandomRespawn();

				}
			}
		}

	}
}
////////////////////////////////////////////////////////////
void Game::render()
{
	if (gameMode == MENU)
	{
		m_mainMenu.draw(m_window);
		
	}
	else if (gameMode == INSTRUCTIONS)
	{
		m_window.draw(getInstructionsBg());
		
	}
	else if (gameMode == GAME_PLAY)
	{
		if (gameAlive == true)
		{
			m_window.draw(m_bgSprite);
			/*if (myBullet.fired == true)
			{
				m_window.draw(myBullet.m_bulletSprite);
			}*/
			m_tank.render(m_window);
			m_window.draw(m_hudSprite);
			m_window.draw(m_timeText);
			m_window.draw(m_rectShape);
			for (sf::Sprite m_wall : m_sprites)
			{
				m_window.draw(m_wall);
			}
			for (sf::Sprite m_targets : m_targetSprites)
			{
				if (target1 == true)
				{
					m_window.draw(m_targetSprites.at(0));
				}
				if (target2 == true)
				{
					m_window.draw(m_targetSprites.at(1));
				}
				if (target3 == true)
				{
					m_window.draw(m_targetSprites.at(2));

				}
			}
			m_window.draw(m_score);
			m_aiTank.render(m_window);
			m_hud.render(m_window);
		}
		if (gameAlive == false)
		{
			m_window.clear(sf::Color(37, 128, 61, 0));
			challangeCounter = 0;
			m_score.setPosition(600, 200);
			m_window.draw(m_score);
			m_window.draw(m_endGame);
			m_window.draw(m_accuracyText);
			m_hud.render(m_window);
		}
	}
	m_window.display();
}

void Game::gameInstructions()
{
	m_window.clear(sf::Color(37,128,61,0));
	m_window.draw(m_instructionsSprite);
	m_window.draw(m_hudSprite);
}

sf::Sprite Game::getInstructionsBg()
{
	return m_instructionsSprite;
}



