#include "Player.h"
#include "Grid.h"



void Player::pickupAmmo(int t_amount)
{
	ammoInReserve += t_amount;
}

void Player::drawUI(sf::RenderWindow& t_window)
{
	t_window.draw(UItext);
}

sf::Sprite& Player::getSprite()
{
	return playerDrawables.playerSprite;
}

//returns position of player in world coordinates
sf::Vector2f Player::getPosition()
{
	return playerDrawables.playerSprite.getPosition();
}




void Player::takeDamage()
{
	currentLives -= 1;
	playerAudio.getHitSoundVoice.play();
	currentStamina -= 10;
}

//adds a life to player
void Player::heal()
{
	currentLives++;
	currentStamina = MAXSTAMINA;
}

//method to handle what animations play
void Player::animate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == true && currentStamina > 0)
	{
		playerDrawables.animateSpeed = playerDrawables.BASEANIMATESPEED * 0.75;
	}
	else
	{
		playerDrawables.animateSpeed = playerDrawables.BASEANIMATESPEED;
	}




	if (moving && reloading == false && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	{
		playerDrawables.animateWalking();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && playerDrawables.shootFrame!=0)
	{
		playerDrawables.resetShootingAnimation();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && reloading == false && ammoInMag > 0)
	{
		playerDrawables.animateShooting(ammoInMag);
	}

	else if (reloading)
	 {
		playerDrawables.animateReload();
	 }
	
}

void Player::updateText()
{
	if (textTimeOut >= MAXTEXTTIMEOUT)
	{
		playerText.setString("");
		textTimeOut = 0;
	}
	if (playerText.getString() != "")
	{
		textTimeOut++;
	}

	playerText.setPosition(getPosition() - sf::Vector2f(playerText.getGlobalBounds().width / 2, 70));
}

void Player::setSkin(int t_value)
{
	if (t_value >= 0 && t_value < 4)
	{
		selectedSkin = t_value;
	}
	else
	{
		selectedSkin = 0;
	}
}




void Player::setPosition(sf::Vector2f t_newPos )
{
	playerDrawables.playerSprite.setPosition(t_newPos);
}

void Player::updateUI(sf::View t_view)
{
	UItext.setPosition(t_view.getCenter() - sf::Vector2f(960, 540));
	stamBar.setPosition(t_view.getCenter() - sf::Vector2f(960,-500));
	playerDrawables.damageSprite.setPosition(t_view.getCenter() - sf::Vector2f(960,540));
}

void Player::initialise()
{
	



	collisionBox.setFillColor(sf::Color::Magenta);
	collisionBox.setSize(sf::Vector2f(60, 60));
	collisionBox.setOrigin(sf::Vector2f(100 / 2, 40 / 2));
	playerDrawables.playerSprite.setOrigin(sf::Vector2f(312 / 2, 206 / 2));
	playerDrawables.loadDrawables();

	detectRadius.setRadius(MOVINGDETECTION);
	detectRadius.setOutlineColor(sf::Color::Black);
	detectRadius.setOutlineThickness(1);
	detectRadius.setFillColor(sf::Color::Transparent);

	detectOrigin = detectRadius.getOrigin() + sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius());

	detectRadius.setOrigin(detectOrigin);

	if (!playerFont.loadFromFile("ART/font.otf"))
	{
		//error
		std::cout << "could not load" << std::endl;
	}
	playerText.setFont(playerFont);
	playerText.setOutlineThickness(1);
	playerText.setOutlineColor(sf::Color::Black);
	playerText.setScale(0.75,0.75);

	stamBar.setFillColor(sf::Color::Green);
	stamBar.setSize(sf::Vector2f(3 * currentStamina, 35));
	stamBar.setPosition(5, 1065);

	UIfont.loadFromFile("ART/font.otf");
	UItext.setFont(UIfont);
	UItext.setFillColor(sf::Color::White);
	UItext.setString("INIT");

		
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].initialise(sf::Color::Red, sf::Vector2f(10,10), 25.0f);
	}

	
}

void Player::draw(sf::RenderWindow& t_window)
{
	
	
	playerDrawables.damageSprite.setColor(sf::Color(255, 0, 0, 255 - currentLives * 25.5));

	for (int i = 0; i < amountBloodStainsOut; i++)
	{
		t_window.draw(playerDrawables.bloodTrailSprite[i]);
		
	}
	t_window.draw(playerDrawables.legsSprite);

	
	t_window.draw(playerDrawables.playerSprite);
	




	t_window.draw(playerDrawables.crosshairSprite);
	t_window.draw(stamBar);
	t_window.draw(playerText);
	t_window.draw(detectRadius);
}

void Player::processInput()
{

	if (canMove)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == true && currentStamina > 0)

		{
			processSprintInput();
		}

		processNormalMove();
		processFireInput();
	}

		
	
}

void Player::processSprintInput()
{
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		playerDrawables.playerSprite.move(-playerSpeed * 1.25, 0);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
	{
		playerDrawables.playerSprite.move(playerSpeed * 1.25, 0);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		playerDrawables.playerSprite.move(0, -playerSpeed * 1.25);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		playerDrawables.playerSprite.move(0, playerSpeed * 1.25);
		keyPressed = true;
	}


	if (currentLives < 3)
	{
		currentStamina-= 0.1;
	}
}

void Player::processNormalMove()
{
	moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true )
	{
		playerDrawables.playerSprite.move(-playerSpeed, 0);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true )
	{
		playerDrawables.playerSprite.move(playerSpeed, 0);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true )
	{
		playerDrawables.playerSprite.move(0, -playerSpeed);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		playerDrawables.playerSprite.move(0, playerSpeed);
		moving = true;
	}

	if (currentStamina < MAXSTAMINA && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == false)
	{
		currentStamina += 0.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && reloading == false && ammoInReserve >0)
	{
		playerAudio.reloadSoundVoice.play();
		reloadTimer = 0;
		reloading = true;
		playerText.setString("Reloading!");
		textTimeOut = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammoInReserve == 0)
	{
		playerAudio.outOfAmmoSoundVoice.play();
		playerText.setString("Im out!");
		textTimeOut = 0;
	}

	if (moving && currentLives <3)
	{
		currentStamina -= 0.05;
	}
}

void Player::processFireInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rateOfFireLimit == ROFTIMEOUTCAP && reloading == false && ammoInMag >0)
	{
		
		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{
			if (bullet[i].bulletState == Bullet::State::chambered && ammoInMag >0)
			{
				
				shooting = true;
				std::cout << "fired Bullet" << std::endl;
				bullet[i].fire(mouseRelativeToWindowPos, getPosition());
				ammoInMag--;
				std::cout << ammoInMag << std::endl;
				rateOfFireLimit = 0;
				playerAudio.shootSound.play();
				break;
			}
		}
	}
	else
	{
		shooting = false;

	}
	
}

void Player::update(sf::RenderWindow& t_window)
{

	if (bloodTrailTimer.getElapsedTime() > sf::seconds(5) && currentLives <3)
	{
		if (amountBloodStainsOut == 30)
		{
			amountBloodStainsOut = 0;
		}
		playerDrawables.bloodTrailSprite[amountBloodStainsOut].setPosition(this->getPosition());
		amountBloodStainsOut++;
		bloodTrailTimer.restart();
	}


	sf::Vector2i mousePosition = sf::Mouse::getPosition(t_window);
	mouseRelativeToWindowPos = t_window.mapPixelToCoords(mousePosition);
	collisionBox.setPosition(getPosition());



	playerRotationAngle = (sf::Vector2f)mouseRelativeToWindowPos - playerDrawables.playerSprite.getPosition();

	if (thor::length(playerRotationAngle) > 5)
	{
		collisionBox.setRotation(thor::polarAngle(playerRotationAngle));
		playerDrawables.playerSprite.setRotation(thor::polarAngle(playerRotationAngle));
		playerDrawables.legsSprite.setRotation(thor::polarAngle(playerRotationAngle));
	}
	

	playerDrawables.crosshairSprite.setPosition((sf::Vector2f)mouseRelativeToWindowPos);

	updateText();
	animate();
	processDetectionRadius();
	playerDrawables.legsSprite.setPosition(getPosition());
	stamBar.setSize(sf::Vector2f(3 * currentStamina, 35));



	
	
	

	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].update();
	}

	if (rateOfFireLimit < ROFTIMEOUTCAP)
	{
		rateOfFireLimit++;
	}

	if (reloading)
	{
		reload();
	}


	UItext.setString("MAGAZINE: " + std::to_string(ammoInMag) + "  " + "AMMO: " + std::to_string(ammoInReserve) + "   " 
		 "RELOADING: " + std::to_string(reloading) + "  " + "STAM: " + std::to_string(currentStamina)
			+"   "+ "LIVES: " + std::to_string(currentLives) + " MOUSEPOS: " + std::to_string(mousePosition.x) + " , " + std::to_string(mousePosition.y)
			+ "  "   + "AMMOINMAG: " + std::to_string(ammoInMag)
			+ "  " + "total: " + std::to_string(ammoInReserve));
}

void Player::reload()
{
	
	if (ammoInReserve > 0)
	{
		if (reloadTimer < 120)
		{
			reloadTimer++;
		}
		else
		{
			refillAmmo();
		}
	}
}

void Player::refillAmmo()
{
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].bulletState = Bullet::State::fired;

	}


	ammoInReserve += ammoInMag;
	ammoInMag = 0;



	if (ammoInReserve >= MAXAMMOPERMAG)
	{
		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{

			
			bullet[i].bulletState = Bullet::State::chambered;
		}
		ammoInMag = MAXAMMOPERMAG;
		reloading = false;
		ammoInReserve -= MAXAMMOPERMAG;
		reloadTimer = 0;
	}
	else
	{
		for (int i = 0; i < ammoInReserve; i++)
		{
			ammoInMag = ammoInReserve;		
			
			bullet[i].bulletState = Bullet::State::chambered;
		}
		reloading = false;
		ammoInReserve = 0;
	}

}

void Player::processDetectionRadius()
{
	if (moving && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		playerDrawables.animateLegsWalking();
		detectRadius.setRadius(MOVINGDETECTION * 1.5);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());

	}

	else if (moving)
	{
		playerDrawables.animateLegsWalking();
		detectRadius.setRadius(MOVINGDETECTION);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());

	}


	else
	{
		detectRadius.setRadius(NOTMOVINGDETECTION);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&& ammoInMag >0 && reloading == false)
		
	{
		detectRadius.setRadius(500);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());
	}
}




//-----------------------drawables--------------------------------


