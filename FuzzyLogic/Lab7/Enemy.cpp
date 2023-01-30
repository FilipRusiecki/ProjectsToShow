#include "Enemy.h"

Enemy::Enemy()
{
	init();
}

void Enemy::init()
{
	circle.setRadius(10);
	circle.setFillColor(sf::Color::Green);
}

void Enemy::update(sf::Time t_deltaTime)
{
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	t_window.draw(circle);
}
