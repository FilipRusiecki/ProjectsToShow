
#include "MainMenu.h"
#include "Game.h"
/// <summary>
/// setup font and message.
/// 
/// Used to get a reference to the font and  
/// load texture and setup sprite and text
/// for each button and positions on screen
void MainMenu::initialise(sf::Font& font)
{
	if (!m_buttonTexture.loadFromFile("./resources/images/button1.png"))			//texture load for the button
	{
		std::cout << "error with button file";
	}
	if (!m_mainMenuTexture.loadFromFile("./resources/images/menu.png"))			//texture load for the menu
	{
		std::cout << "Error... Loading main menu texture" << std::endl;
	}

	m_mainMenuSprite.setTexture(m_mainMenuTexture);			//setting the texture of the menu
	m_topOffset = 100;				//the off set of the buttons from the top 
	m_verticalSpacing = 100;		//the spacing between the buttons
	m_buttonWidth = 180;			//the width of the buttons
	m_leftOffset = (1440 - m_buttonWidth) / 2;	//the offset of the buttons from the left hand side of the screen
	m_leftOffset1 = (1400 - m_buttonWidth) / 2;//the offset of the text from the left hand side of the screen
	m_buttonHeight = 65;						//the height of the buttons 
	int textDropOffset = 10;						//the text offset from the top of the screen
	sf::String m_menuTexts[] = { "Play", "Controls", "Exit",};		//the string to display the text for apropriate button

	/// for loop to setup menu buttons in an array
	/// keeps them in a centre nicely laid out
	/// scales them to texture size so they look to scale
	/// 
	m_foont = font;		//setting the passed font
	for (int i = 0; i < m_optionCount; i++)					//loop to go through all the options 
	{
		m_buttonSprites[i].setTexture(m_buttonTexture);		//setting texture to each sprite 
		m_buttonSprites[i].setPosition(m_leftOffset1, m_verticalSpacing * i + m_topOffset);	//setting the positions of the buttons
		sf::Vector2u textureSize = m_buttonTexture.getSize();		//new variable with the button size
		m_buttonSprites[i].setScale(m_buttonWidth / textureSize.x, m_buttonHeight / textureSize.y);		//setting scale of the buttons

		// sets font up for the array of text shapes that display over the buttons
		m_buttonTexts[i].setFont(m_foont);		//setting the font for the play buttons 
		m_buttonTexts[i].setOutlineColor(sf::Color::Black);
		m_buttonTexts[i].setOutlineThickness(3.0f);
		m_buttonTexts[i].setScale(1.0f,1.0f);
		m_buttonTexts[i].setString(m_menuTexts[i]);	//setting the custom string for the buttons
		sf::FloatRect textSize = m_buttonTexts[i].getGlobalBounds();	//getting the global bounds of the text.
		float textOffset = (m_buttonWidth - textSize.width) / 2;		//setting the offset of the text of every button.
		m_buttonTexts[i].setPosition(m_leftOffset + textOffset, m_verticalSpacing * i + m_topOffset + textDropOffset);
	}
}
/// <summary>
/// check current position of the mouse for intersection with
/// location of buttons using locations and offsets rather than rectangles
/// for intersection (create said so 'imaginary' columns and rows, then mouse x/y 
/// values are compared to see if they are intersecting columns' then rows' x/y values
/// </summary>
void MainMenu::update(sf::Window& window, int& t_gameMode)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mouseLocation;		//new variable for mouse location
		mouseLocation = sf::Mouse::getPosition(window);		//setting the mouse location to a variable
		if (mouseLocation.x > m_leftOffset && mouseLocation.x < m_leftOffset + m_buttonWidth)		//if statement for the buttons if the mouse is in a certain position on the screen
		{
			if (mouseLocation.y > m_topOffset && mouseLocation.y && mouseLocation.y < m_topOffset + m_buttonHeight)
			{
				t_gameMode = GAME_PLAY;		//set gamemode to play
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing && mouseLocation.y < m_topOffset + m_verticalSpacing + m_buttonHeight)
			{
				t_gameMode = INSTRUCTIONS;	//set gamemode to instructions
			}
			if (mouseLocation.y > m_topOffset + m_verticalSpacing * 2 && mouseLocation.y < m_topOffset + m_verticalSpacing * 2 + m_buttonHeight)
			{
				window.close();				//set gamemode to exit the game
			}
		}
	}
}
/// <summary>
///  draw menu text over buttons
/// </summary>
void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(m_mainMenuSprite);
	for (int i = 0; i < m_optionCount; i++)
	{
		window.draw(m_buttonSprites[i]); //drawing all the button sprites
		window.draw(m_buttonTexts[i]);	//drawing all the text for the buttons
	}
}