#include "Tank.h"
#include <iostream>

Tank::Tank(sf::Texture const& texture, std::vector<sf::Sprite>& m_wallSprites)//, sf::Vector2f const& pos)
	: m_texture(texture)
	, m_wallSprites(m_wallSprites)
{
	initSprites();
}

void Tank::update(double dt, sf::Vector2f& t_pos,std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase)
{
	
	handleKeyInput();
	float radToDeg = (MathUtility::DEG_TO_RAD * m_rotation);				//converting radians to degress
	float newXPos = t_pos.x + cos(radToDeg) * m_speed * (dt / 1000);
	float newYPos = t_pos.y + sin(radToDeg) * m_speed * (dt / 1000);

	t_pos.x = newXPos;
	t_pos.y = newYPos;

	m_tankBase.setPosition(t_pos.x, t_pos.y);			//setting new pos
	m_tankBase.setRotation(m_rotation);					//setting the new rotation

	m_turret.setRotation(m_turretRotation); 			//setting new rotation
	m_turret.setPosition(m_tankBase.getPosition());		//setting new pos

	slowSpeed();										//function call

	m_pool.update(dt, m_wallSprites, t_funcApplyDamage, m_tankBase);


	if (m_fireRequested)
	{
		m_shootTimer -= dt;
		if (m_shootTimer <= 0)
		{
			m_shootTimer = s_TIME_BETWEEN_SHOTS;
			m_fireRequested = false;
		}
	}
	if (checkWallCollision() == true)					//check collisions
	{
		deflect();										//function call to deflect
	}
	
}

void Tank::render(sf::RenderWindow& window)			//drawing the tank base and turret
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	m_pool.render(window);
}


void Tank::handleKeyInput()			//void to check for button presses
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		//if d is clicked 
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		//if s is clicked 
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		//if a is clicked 
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		//if w is clicked 
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J ))		//if j is clicked 
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))		//if k is clicked 
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))		//if c is clicked 
	{
		centreTurret();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		requestFire();
	}

}

void Tank::increaseTurretRotation()					//function to increase the rotation of the turret (rotate left)
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation += 0.8;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()						//function to decrease the rotation of the turret (rotate right)
{
	m_previousTurretRotation = m_turretRotation;
	m_turretRotation -= 0.8; 
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}
				
void Tank::centreTurret()				//function to recenter the turret to its original pos
{
	m_turretRotation = m_rotation;

}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)		//for loop to cycle throgh all the walls.
	{
		if (CollisionDetector::collision(m_turret, sprite) || CollisionDetector::collision(m_tankBase, sprite))		//collision detection between the tank and walls.
		{
			return true;
		}
	}
	return false;
}

void Tank::deflect()
{
	// In case tank was rotating.
	adjustRotation();

	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_previousPosition = m_tankBase.getPosition();

		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
}

void Tank::adjustRotation()
{
	//enter code here
	 // If tank was rotating...
	if (m_rotation != m_previousRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_turretRotation = m_previousTurretRotation;
	}
}

sf::Vector2f Tank::getPosition() const
{
	return m_tankBase.getPosition();
}

sf::Sprite Tank::getTurretSprite() const
{
	return m_turret;
}

sf::Sprite Tank::getBaseSprite() const
{
	return m_tankBase;
}

void Tank::initSprites()
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	//m_tankBase.setPosition(m_tankBase.getPosition());

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	//m_turret.setPosition(m_tankBase.getPosition());

}

//void to set the position of the tank
void Tank::setPosition(sf::Vector2f t_pos)
{
	t_pos = m_position;
	m_tankBase.setPosition(t_pos);
	m_turret.setPosition(t_pos);
}

void Tank::increaseSpeed()			//function to decrease the speed
{
	m_speed += 1.0;
	if (m_speed < 100.0)
	{
		m_speed += 2;
	}
}

//////////////////////////////////////////////////////////// 
void Tank::decreaseSpeed()			//function to decrease the speed
{
	if (m_speed < -100)				//simple function to slow it down if speed is over 100
	{
		m_speed = -2;
	}
	m_speed -= 1.0;
	if (m_speed > -100.0)			//simple function to slow it down if speed is under 100
	{
		m_speed -= 1;
	}
}

////////////////////////////////////////////////////////////
void Tank::increaseRotation()		//function to decrease the rotation of the tank (rotate right)
{
	m_previousRotation = m_rotation;
	m_rotation += 1.0;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}

}

////////////////////////////////////////////////////////////
void Tank::decreaseRotation()		//function to decrease the rotation of the tank(rotate left)
{
	m_previousRotation = m_rotation;
	m_rotation -= 1.0;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}

}

////////////////////////////////////////////////////////////
void Tank::requestFire()
{
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		sf::Vector2f tipOfTurret(m_turret.getPosition().x + 2.0f, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		tipOfTurret.y += std::sin(MathUtility::DEG_TO_RAD * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		m_pool.create(m_texture, tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
}

double Tank::getTurretRotation()		//return turret rotation
{
	return m_turretRotation;
}

sf::Vector2f Tank::getTurretPos()		//return turret pos
{
	return m_turret.getPosition();
}

void Tank::slowSpeed() //function to slow the tank
{
	m_speed = m_speed * 0.99;
}

