#include "Player.h"

Player::Player()
{
	init();
}

void Player::init()
{
	circle.setRadius(10);
	circle.setFillColor(sf::Color::Magenta);
	circle.setPosition(100, 550);
}

void Player::update(sf::Time t_deltaTime)
{
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(circle);
}
