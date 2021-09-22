#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Settings {
	sf::Sprite bgSprite;
	sf::Texture bgTexture;
	sf::Text settingInstructions;
	sf::Font m_fonts;


public:
	void init();
	void draw(sf::RenderWindow& m_window);
	void update();
	void loadContent();



};