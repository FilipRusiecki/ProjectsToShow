#include "Bullet.h"


void Bullet::update()
{
	if (bulletState == State::moving)
	{
		bulletBody.move(velocity);
		
	}
	if (timeoutCounter.getElapsedTime() > sf::seconds(10))
	{
		bulletState = State::chambered;

		velocity = { 0,0 };
	}
}

void Bullet::initialise(sf::Color t_bulletColor, sf::Vector2f t_bulletSize,float t_projectileSpeed)
{
	bulletBody.setFillColor(t_bulletColor);
	bulletBody.setSize(t_bulletSize);
	projectileSpeed = t_projectileSpeed;
}

void Bullet::fire(sf::Vector2f t_goalLocation, sf::Vector2f t_startPosition)
{
	bulletBody.setPosition(t_startPosition);
	velocity = t_goalLocation - bulletBody.getPosition();
	thor::setLength(velocity, float(projectileSpeed));
	timeoutCounter.restart();
	bulletState = State::moving;
}
