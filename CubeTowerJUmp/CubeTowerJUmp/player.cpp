#include "player.h"

void player::playerConst()
{
	shape.setSize(size);
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(275, 850.0 - size.y);

}
