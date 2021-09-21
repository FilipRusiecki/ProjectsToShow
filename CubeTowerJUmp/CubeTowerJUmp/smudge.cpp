#include "smudge.h"


Smudge::Smudge()
{
	setupSmudge();
}

void Smudge::setupSmudge()
{
	playerSmudge.setFillColor(sf::Color::Black);
	playerSmudge.setSize(size);
}