#include "Consumable.h"


void Consumable::draw(sf::RenderWindow& t_window)
{
	if (active)
	{
		t_window.draw(consumableSprite);
	}
}

sf::Vector2f Consumable::getPosition()
{
	return this->consumableSprite.getPosition();
}

void Consumable::pickup(Player t_player)
{
	

}
