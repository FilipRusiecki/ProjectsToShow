#include "Weather.h"

void Weather::init()
{
	if (!snowTexture.loadFromFile("ART/snowflake.png"))
	{
		//error
	}

	

	for (int i = 0; i < amountPrecipitation; i++)
	{
		precipitationSprite[i].setTexture(snowTexture);
		precipitationSprite[i].setPosition(rand() % 1920, rand() % 1080);
		precipitationSprite[i].setScale(.005, .005);
		velocity[i] = sf::Vector2f(0.5, rand() % 7 + 1);
	}


}

void Weather::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < amountPrecipitation; i++)
	{
		t_window.draw(precipitationSprite[i]);
	}
	

}

void Weather::update(sf::RenderWindow& t_window)
{
	for (int i = 0; i < amountPrecipitation; i++)
	{
		precipitationSprite[i].move(velocity[i]);
		precipitationSprite[i].rotate(0.3);
		



		if (precipitationSprite[i].getPosition().x > t_window.mapPixelToCoords(windowSize).x || precipitationSprite[i].getPosition().y > t_window.mapPixelToCoords(windowSize).y
			|| precipitationSprite[i].getPosition().x < t_window.mapPixelToCoords(windowEnds).x || precipitationSprite[i].getPosition().y < t_window.mapPixelToCoords(windowEnds).y)
		{
			sf::Vector2f pos = t_window.mapPixelToCoords(sf::Vector2i(rand()%1920,0));

			precipitationSprite[i].setPosition(pos);
		}
	}
	
}
