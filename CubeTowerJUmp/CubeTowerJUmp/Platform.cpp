#include "Platform.h"


Platform::Platform()
{
	setupPlatform();
}



void Platform::setupPlatform()
{
	platform.setFillColor(sf::Color::Black);
	size.x = rand() % 150 + 60;
	size.y = 15.0f;
	platform.setSize(size);


}

