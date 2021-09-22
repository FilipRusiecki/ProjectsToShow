#include "Settings.h"

void Settings::init()
{
	loadContent();
	bgSprite.setTexture(bgTexture);			//Character Customization background
	bgSprite.scale(1.0f, 1.0f);				//setting scale

	settingInstructions.setFillColor(sf::Color::White);
	settingInstructions.setCharacterSize(24);
	settingInstructions.setString("Press Num One = Audio off \n Press Num Two = Audio On ");
	settingInstructions.setPosition(500, 400);
	settingInstructions.setFont(m_fonts);
}

void Settings::draw(sf::RenderWindow& m_window)
{
	m_window.draw(bgSprite);
	m_window.draw(settingInstructions);

}

void Settings::update()
{


}

void Settings::loadContent()
{
	if (!bgTexture.loadFromFile("ART/INSTRUCTIONS/bg.png"))
	{
		std::cout << "error with image file file";
	}

	if (!m_fonts.loadFromFile("ART/FONTS/rough.otf"))
	{
		std::cout << "error with font file ";
	}
}
