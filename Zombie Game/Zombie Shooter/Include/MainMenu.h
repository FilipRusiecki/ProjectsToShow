#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"


class MainMenu
{
	/// Number of buttons on our menu
	static const int m_optionCount = 6;
	/// green button background
	sf::Texture m_buttonTexture;
	/// array of sprites used to display buttons
	sf::Sprite m_buttonSprites[m_optionCount];
	/// local refrence to font used by whole game
	sf::Font m_font; 
	/// array of text objects for text on buttons
	sf::Text m_buttonTexts[m_optionCount];

	/// top left of area used for menu
	float m_topOffset;
	/// top left of area used for menu
	float m_leftOffset;
	/// gap in pixels between tops of buttons
	float m_verticalSpacing;
	/// width in pixels of all buttons
	float m_buttonWidth;
	/// height of button in pixels must be less than vertical spacing
	float m_buttonHeight;




	sf::Texture titleTexture;
	sf::Sprite titleSprite;
	sf::IntRect rectSourceSprite;
	float totalElapsed = 0;
	int animationframe = 0;


	sf::SoundBuffer m_buttonClick;
	sf::Sound m_clickSound;

public:
	void anim();
	void initialise(sf::Font&);
	void draw(sf::RenderWindow&);
	void update(sf::Window&, int& t_gameMode);


};
