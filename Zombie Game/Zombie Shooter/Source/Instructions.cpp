#include "Instructions.h"


void instructions::init()
{
	loadContent();
	bgSprite.setTexture(bgTexture);			//instructions background
	bgSprite.scale(1.0f, 1.0f);				//setting scale

							
	wasdSprite.setTexture(wasdTexture);		//setting w a s d keys texture
	wasdSprite.setPosition(750, 350);		//setting pos


	shiftSprite.setTexture(shiftTexture);	//setting shift key texture
	shiftSprite.setPosition(470, 447); 		//setting pos
	shiftSprite.scale(0.2f, 0.2f);			//setting scale
	 

	rSprite.setTexture(rTexture);			//setting r key texture
	rSprite.setPosition(1050, 350); 		//setting pos
	rSprite.scale(0.18f, 0.18f);			//setting scale


	escSprite.setTexture(escTexture);			//setting esc key texture
	escSprite.setPosition(625, 300); 		//setting pos
	escSprite.scale(0.18f, 0.18f);			//setting scale


	wKey.setFont(m_font);
	wKey.setFillColor(sf::Color::White);
	wKey.setCharacterSize(24);
	wKey.setString("Up");
	wKey.setPosition(870, 320);


	aKey.setFont(m_font);
	aKey.setFillColor(sf::Color::White);
	aKey.setCharacterSize(24);
	aKey.setString("Left");
	aKey.setPosition(770, 420);


	sKey.setFont(m_font);
	sKey.setFillColor(sf::Color::White);
	sKey.setCharacterSize(24);
	sKey.setString("Down");
	sKey.setPosition(850, 540);


	dKey.setFont(m_font);
	dKey.setFillColor(sf::Color::White);
	dKey.setCharacterSize(24);
	dKey.setString("Right");
	dKey.setPosition(950, 420);


	shiftKey.setFont(m_font);
	shiftKey.setFillColor(sf::Color::White);
	shiftKey.setCharacterSize(24);
	shiftKey.setString("Sprint");
	shiftKey.setPosition(550, 420);


	rKey.setFont(m_font);
	rKey.setFillColor(sf::Color::White);
	rKey.setCharacterSize(24);
	rKey.setString("Reload");
	rKey.setPosition(1045, 320);


	escKey.setFont(m_font);
	escKey.setFillColor(sf::Color::White);
	escKey.setCharacterSize(24);
	escKey.setString("Back");
	escKey.setPosition(635, 270);
}


//draw function to draw everything thats needed
void instructions::draw(sf::RenderWindow& m_window)
{
	m_window.draw(bgSprite);
	m_window.draw(wasdSprite);
	m_window.draw(rSprite);
	m_window.draw(shiftSprite);
	m_window.draw(escSprite);
	m_window.draw(wKey);
	m_window.draw(aKey);
	m_window.draw(sKey);
	m_window.draw(dKey);
	m_window.draw(shiftKey);
	m_window.draw(rKey);
	m_window.draw(escKey);
}

void instructions::update()
{

}


//loading all the content from files thats needede
void instructions::loadContent()
{ 
	if (!bgTexture.loadFromFile("ART/INSTRUCTIONS/bg.png"))
	{
		std::cout << "error with image file file";
	} 

	if (!wasdTexture.loadFromFile("ART/INSTRUCTIONS/wasd.png"))
	{
		std::cout << "error with image file file";
	}

	if (!shiftTexture.loadFromFile("ART/INSTRUCTIONS/shift.png"))
	{
		std::cout << "error with image file file";
	}

	if (!rTexture.loadFromFile("ART/INSTRUCTIONS/r.png"))
	{
		std::cout << "error with image file file";
	}

	if (!escTexture.loadFromFile("ART/INSTRUCTIONS/esc.png"))
	{
		std::cout << "error with image file file";
	}

	if (!m_font.loadFromFile("ART/FONTS/rough.otf"))
	{
		std::cout << "error with font file file";
	}
}
