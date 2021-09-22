#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Globals.h"


class MainMenu
{
	/// Number of buttons on our menu
	static const int m_optionCount = 3;
	/// green button background
	sf::Texture m_buttonTexture;
	/// array of sprites used to display buttons
	sf::Sprite m_buttonSprites[m_optionCount];
	/// local refrence to font used by whole game
	sf::Font m_foont;
	/// array of text objects for text on buttons
	sf::Text m_buttonTexts[m_optionCount];

	/// top left of area used for menu
	float m_topOffset;
	/// top left of area used for menu
	float m_leftOffset;
	float m_leftOffset1;
	/// gap in pixels between tops of buttons
	float m_verticalSpacing;
	/// width in pixels of all buttons
	float m_buttonWidth;
	/// height of button in pixels must be less than vertical spacing
	float m_buttonHeight;

public:
	sf::Texture m_mainMenuTexture;		//texture for the menu
	sf::Sprite m_mainMenuSprite;		//sprite for the menu
	void initialise(sf::Font&);			//void to initialise everything in the menu
	void draw(sf::RenderWindow&);		//void to draw the menu
	void update(sf::Window&, int& t_gameMode);	//void to update the menu

};
