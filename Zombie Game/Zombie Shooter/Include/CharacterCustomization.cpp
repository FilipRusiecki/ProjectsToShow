#include "CharacterCustomization.h"


void CharacterCustomization::init()
{
	loadContent();
	bgSprite.setTexture(bgTexture);			//Character Customization background
	bgSprite.scale(1.0f, 1.0f);				//setting scale
	greenBox.setFillColor(sf::Color(44, 150, 72, 190));
	greenBox.setSize(sf::Vector2f(600, 600));
	greenBox.setPosition(650, 200);
	//boxes behind the player skins 
	skin1.setFillColor(sf::Color(227, 172, 43));
	skin2.setFillColor(sf::Color(105, 104, 101));
	skin3.setFillColor(sf::Color(105, 104, 101));
	skin4.setFillColor(sf::Color(105, 104, 101));
	skin1.setSize(sf::Vector2f(100, 100));
	skin2.setSize(sf::Vector2f(100, 100));
	skin3.setSize(sf::Vector2f(100, 100));
	skin4.setSize(sf::Vector2f(100, 100));
	skin1.setPosition(900, 300);
	skin2.setPosition(1050, 450);
	skin3.setPosition(750, 450);
	skin4.setPosition(900, 600);
	//player skin 1
	player1.setTexture(playerTexture1);
	player1.setPosition(890, 295);
	player1.setScale(0.5, 0.5);
	//player skin 2
	player2.setTexture(playerTexture2);
	player2.setPosition(1040, 445);
	player2.setScale(0.5, 0.5);
	//player skin 3
	player3.setTexture(playerTexture3);
	player3.setPosition(740, 445);
	player3.setScale(0.5, 0.5);
	//player skin 4
	player4.setTexture(playerTexture4);
	player4.setPosition(890, 595);
	player4.setScale(0.5, 0.5);
	//setting the size of the text
	arrowDown.setCharacterSize(12);
	arrowUp.setCharacterSize(12);
	arrowLeft.setCharacterSize(12);
	arrowRight.setCharacterSize(12);
	//setting the font of the text
	arrowDown.setFont(m_font);
	arrowUp.setFont(m_font);
	arrowLeft.setFont(m_font);
	arrowRight.setFont(m_font);
	//setting the color of the text
	arrowDown.setFillColor(sf::Color::White);
	arrowUp.setFillColor(sf::Color::White);
	arrowLeft.setFillColor(sf::Color::White);
	arrowRight.setFillColor(sf::Color::White);
	//setting the pos of the text
	arrowDown.setPosition(900,700);
	arrowUp.setPosition(900,300);
	arrowLeft.setPosition(750,450);
	arrowRight.setPosition(1050,450);
	//setting the string of the text
	arrowDown.setString("ArrowDown");
	arrowUp.setString("ArrowUp");
	arrowLeft.setString("ArrowLeft");
	arrowRight.setString("ArrowRight");
	
}

void CharacterCustomization::draw(sf::RenderWindow& m_window)
{
	m_window.draw(bgSprite);
	m_window.draw(greenBox);
	m_window.draw(skin1);
	m_window.draw(skin2);
	m_window.draw(skin3);
	m_window.draw(skin4);
	m_window.draw(player1);
	m_window.draw(player2);
	m_window.draw(player3);
	m_window.draw(player4);
	m_window.draw(arrowDown);
	m_window.draw(arrowUp);
	m_window.draw(arrowLeft);
	m_window.draw(arrowRight);
}

void CharacterCustomization::update()
{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			selectedSkin = 0;
			if (selectedSkin == 0)
			{
				skin1.setFillColor(sf::Color(227, 172, 43));
				skin2.setFillColor(sf::Color(105, 104, 101));
				skin3.setFillColor(sf::Color(105, 104, 101));
				skin4.setFillColor(sf::Color(105, 104, 101));
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			selectedSkin = 1;
			if (selectedSkin == 1)
			{
				skin2.setFillColor(sf::Color(227, 172, 43));
				skin1.setFillColor(sf::Color(105, 104, 101));
				skin3.setFillColor(sf::Color(105, 104, 101));
				skin4.setFillColor(sf::Color(105, 104, 101));
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			selectedSkin = 2;
			if (selectedSkin == 2)
			{
				skin3.setFillColor(sf::Color(227, 172, 43));
				skin2.setFillColor(sf::Color(105, 104, 101));
				skin1.setFillColor(sf::Color(105, 104, 101));
				skin4.setFillColor(sf::Color(105, 104, 101));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			selectedSkin = 3;
			if (selectedSkin == 3)
			{
				skin4.setFillColor(sf::Color(227, 172, 43));
				skin2.setFillColor(sf::Color(105, 104, 101));
				skin3.setFillColor(sf::Color(105, 104, 101));
				skin1.setFillColor(sf::Color(105, 104, 101));
			}

		}


}

void CharacterCustomization::loadContent()
{

	if (!bgTexture.loadFromFile("ART/INSTRUCTIONS/bg.png"))
	{
		std::cout << "error with image file ";
	}

	if (!playerTexture1.loadFromFile("ART/player/Body/survivor-move_rifle_0.png"))
	{
		std::cout << "error with player texture 1 file ";
	}

	if (!playerTexture2.loadFromFile("ART/player/Body/player1.png"))
	{
		std::cout << "error with player texture 1 file ";
	}

	if (!playerTexture3.loadFromFile("ART/player/Body/player2.png"))
	{
		std::cout << "error with player texture 1 file ";
	}

	if (!playerTexture4.loadFromFile("ART/player/Body/player3.png"))
	{
		std::cout << "error with player texture 1 file ";
	}

	if (!m_font.loadFromFile("ART/FONTS/rough.otf"))
	{
		std::cout << "error with font file ";
	}
}

int CharacterCustomization::getSkin()
{
	return selectedSkin;
}
