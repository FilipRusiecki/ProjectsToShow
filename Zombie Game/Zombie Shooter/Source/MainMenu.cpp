
#include "MainMenu.h"

/// Used to get a reference to the font and  
/// load texture and setup sprite and text
/// for each button and positions on screen
void MainMenu::initialise(sf::Font& font)
{
	m_topOffset = 100;
	m_verticalSpacing = 80;
	m_buttonWidth = 300;
	m_leftOffset = (300 - m_buttonWidth);
	m_buttonHeight = 70;
	int textDropOffset = 25;
	sf::String m_menuTexts[] = { "New Game", "Play", "Customize", "Controls", "Settings", "Exit" };
	m_font = font;
	/// display error if button.png doesnt load properly
	if (!m_buttonTexture.loadFromFile("ART/MENU/button.png"))
	{
		std::cout << "error with button file";
	}


	if (!m_buttonClick.loadFromFile("MUSIC/button.ogg"))
	{
		std::cout << "error with button sound file";
	}


	if (!titleTexture.loadFromFile("ART/MENU/spritesheet.png")) { 

		std::cout << "error with button sound file";
		totalElapsed = 0; animationframe = 0;
	}

	titleSprite.setTexture(titleTexture);
	titleSprite.setPosition(550, 10);
	titleSprite.setTextureRect(rectSourceSprite);
	totalElapsed = 0;
	animationframe = 0;
	rectSourceSprite.height = 430;
	rectSourceSprite.width = 1292;

	m_clickSound.setBuffer(m_buttonClick);
	/// for loop to setup menu buttons in an array
	/// keeps them in a centre nicely laid out
	/// scales them to texture size so they look to scale
	/// 
	for (int i = 0; i < m_optionCount; i++)
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);
		m_buttonSprites[i].setPosition(m_leftOffset, m_verticalSpacing * i + m_topOffset);
		sf::Vector2u textureSize = m_buttonTexture.getSize();
		m_buttonSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeight / textureSize.y);

		// sets font up for the array of text shapes that display over the buttons
		m_buttonTexts[i].setFont(m_font);
		m_buttonTexts[i].setString(m_menuTexts[i]);
		m_buttonTexts[i].setFillColor(sf::Color::White);
		m_buttonTexts[i].setCharacterSize(20);
		sf::FloatRect textSize = m_buttonTexts[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / 2;
		m_buttonTexts[i].setPosition(m_leftOffset + textOffset, m_verticalSpacing * i + m_topOffset + textDropOffset);
	}
}
/// check current position of the mouse for intersection with
/// location of buttons using locations and offsets rather than rectangles
/// for intersection (create said so 'imaginary' columns and rows, then mouse x/y 
/// values are compared to see if they are intersecting columns' then rows' x/y values

void MainMenu::update(sf::Window& window, int& t_gameMode)
{
	anim();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;
		mouseLocation = sf::Mouse::getPosition(window);
		if (mouseLocation.x > m_leftOffset && mouseLocation.x < m_leftOffset + m_buttonWidth)
		{
			if (mouseLocation.y > m_topOffset && mouseLocation.y && mouseLocation.y < m_topOffset + m_buttonHeight)
			{
				m_clickSound.play();
				t_gameMode = PLAY;	//new game
				
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing && mouseLocation.y < m_topOffset + m_verticalSpacing + m_buttonHeight)
			{
				//play game
				m_clickSound.play();
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 2 && mouseLocation.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeight)
			{
				m_clickSound.play();
				t_gameMode = CHARACTER_CUSTOMIZATION;	//character customization
				
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 3 && mouseLocation.y < m_topOffset + m_verticalSpacing * 3 + m_buttonHeight)
			{
				m_clickSound.play();
				t_gameMode = CONTROLS;	//controlls
				
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 4 && mouseLocation.y < m_topOffset + m_verticalSpacing * 4 + m_buttonHeight)
			{
				m_clickSound.play();
				t_gameMode = SETTINGS;	//SETTINGS
				
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 5 && mouseLocation.y < m_topOffset + m_verticalSpacing * 5 + m_buttonHeight)
			{
				m_clickSound.play();
				window.close();		//exit

			}

		}
	}

	
}


///  draw menu text over buttons

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_optionCount; i++)
	{
		window.draw(m_buttonSprites[i]);
		window.draw(m_buttonTexts[i]);
		window.draw(titleSprite);
	}

}

void  MainMenu::anim()
{
	totalElapsed++;
	if (totalElapsed > 5)
	{
		totalElapsed = 0;
		animationframe++;
		if (animationframe > 10)
		{
			animationframe = 0;

		}
	}

	int col = animationframe % 10;
	int row = animationframe / 1;
	rectSourceSprite.height = 430;
	rectSourceSprite.width = 1292;
	rectSourceSprite.left = col * rectSourceSprite.width;
	titleSprite.setTextureRect(rectSourceSprite);
}
