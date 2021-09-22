#include "PlayerDrawables.h"
void PlayerDrawables::loadDrawables()
{
	if (!bloodTrailTexture.loadFromFile("ART/bloodTrail.png"))
	{
		std::cout << "error loading blood trail sprite" << std::endl;
	}

	for (int i = 0; i < 30; i++)

	{
		bloodTrailSprite[i].setTexture(bloodTrailTexture);
		bloodTrailSprite[i].setScale(.1, .1);
		bloodTrailSprite[i].setOrigin(bloodTrailSprite[i].getGlobalBounds().width / 2, bloodTrailSprite[i].getGlobalBounds().height / 2);
	}

	if (!crosshairTexture.loadFromFile("ART/Cursor.png"))
	{
		//error
	}
	crosshairSprite.setTexture(crosshairTexture);



	if (!damageTexture.loadFromFile("ART/damageEffect.png"))
	{
		std::cout << "error loading damage sprite" << std::endl;
	}

	damageSprite.setTexture(damageTexture);


	for (int i = 0; i < 20; i++)
	{

		if (!playerTexture.loadFromFile("ART/player/Body/spritesheet.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!playerTexture1.loadFromFile("ART/player/Body/spritesheet1.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!playerTexture2.loadFromFile("ART/player/Body/spritesheet2.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!playerTexture3.loadFromFile("ART/player/Body/spritesheet3.png"))
		{
			std::cout << "error loading file" << std::endl;
		}

		if (!legsTexture.loadFromFile("ART/player/legs/spritesheet.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}




	for (int i = 0; i < SHOOTSPRITEFRAMES; i++)
	{
		if (!shootingTexture.loadFromFile("ART/player/Shooting/spritesheet.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!shootingTexture1.loadFromFile("ART/player/Shooting/spritesheet1.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!shootingTexture2.loadFromFile("ART/player/Shooting/spritesheet2.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!shootingTexture3.loadFromFile("ART/player/Shooting/spritesheet3.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}

	for (int i = 0; i < AMOUNTRELOADFRAMES; i++)
	{
		if (!reloadTexture.loadFromFile("ART/player/Reloading/spritesheet.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!reloadTexture1.loadFromFile("ART/player/Reloading/spritesheet1.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!reloadTexture2.loadFromFile("ART/player/Reloading/spritesheet2.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
		if (!reloadTexture3.loadFromFile("ART/player/Reloading/spritesheet3.png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}


	legsSprite.setScale(.5, .5);
	playerSprite.setScale(.5, .5);

	legsSprite.setOrigin(playerSprite.getOrigin() + sf::Vector2f(-30, -55));
}






void PlayerDrawables::animateLegsWalking()
{
	legsMoveFrameCounter++;

	if (legsMoveFrameCounter >= animateSpeed)
	{

		legsMoveFrameCounter = 0;
		legsSprite.setTexture(legsTexture);
		legsSprite.setTextureRect(sf::IntRect((172 * moveFrame), 0, 172, 124));
		legsMoveFrame++;
		if (legsMoveFrame == AMOUNTFRAMES)
		{
			legsMoveFrame = 0;
		}


	}
}


//animates player torso when walking
void PlayerDrawables::animateWalking()
{
	reloadFrame = 0;

	playerSprite.setTextureRect(sf::IntRect((313 * moveFrame), 0, 313, 206));
	moveFrameChangeCounter++;

	switch (selectedSkin)
	{
	case 0:
		playerSprite.setTexture(playerTexture);
		break;
	case 1:
		playerSprite.setTexture(playerTexture1);
		break;
	case 2:
		playerSprite.setTexture(playerTexture2);
		break;
	case 3:
		playerSprite.setTexture(playerTexture3);
		break;
	default:
		playerSprite.setTexture(playerTexture);
	}



	if (moveFrameChangeCounter >= animateSpeed)
	{
		moveFrameChangeCounter = 0;
		playerSprite.setTextureRect(sf::IntRect((313 * moveFrame), 0, 313, 206));
		moveFrame++;
		if (moveFrame == AMOUNTFRAMES)
		{
			moveFrame = 0;
		}


	}
}

void PlayerDrawables::animateReload()
{


	playerSprite.setTextureRect(sf::IntRect((322 * reloadFrame), 0, 322, 217));

	switch (selectedSkin)
	{
	case 0:
		playerSprite.setTexture(reloadTexture);
		break;
	case 1:
		playerSprite.setTexture(reloadTexture1);
		break;
	case 2:
		playerSprite.setTexture(reloadTexture2);
		break;
	case 3:
		playerSprite.setTexture(reloadTexture3);
		break;
	default:
		playerSprite.setTexture(reloadTexture);
	}

	reloadFrameChangeCounter++;
	if (reloadFrameChangeCounter > reloadAnimateSpeed)
	{
		reloadFrameChangeCounter = 0;



		playerSprite.setTextureRect(sf::IntRect((322 * reloadFrame), 0, 322, 217));
		reloadFrame++;
		if (reloadFrame == AMOUNTRELOADFRAMES)
		{
			reloadFrame = 0;

		}
	}
}

void PlayerDrawables::animateShooting(int t_ammoInMag)
{
	reloadFrame = 0;

	
		playerSprite.setTextureRect(sf::IntRect((336 * shootFrame), 0, 345, 206));
		shootFrameChangeCounter++;

		switch (selectedSkin)
		{
		case 0:
			playerSprite.setTexture(shootingTexture);
			break;
		case 1:
			playerSprite.setTexture(shootingTexture1);
			break;
		case 2:
			playerSprite.setTexture(shootingTexture2);
			break;
		case 3:
			playerSprite.setTexture(shootingTexture3);
			break;
		default:
			playerSprite.setTexture(shootingTexture);

		}
			if (shootFrameChangeCounter > shootAnimateSpeed)
			{
				shootFrameChangeCounter = 0;

				playerSprite.setTextureRect(sf::IntRect((336 * shootFrame), 0, 345, 206));
				shootFrame++;
				if (shootFrame == SHOOTSPRITEFRAMES)
				{
					shootFrame = 0;
				}

			}
	
}

void PlayerDrawables::resetShootingAnimation()
{
	shootFrame = 0;
}


