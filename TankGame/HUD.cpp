#include "HUD.h"

////////////////////////////////////////////////////////////
HUD::HUD(sf::Font& hudFont)
    : m_textFont(hudFont)
{
    m_gameStateText.setFont(hudFont);
    m_gameStateText.setCharacterSize(30);
    m_gameStateText.setFillColor(sf::Color::Blue);
    m_gameStateText.setPosition(sf::Vector2f(480, 5));
    m_gameStateText.setString("Game Running");

    //Setting up our hud properties 
    m_hudOutline.setSize(sf::Vector2f(1440.0f, 40.0f));
    m_hudOutline.setFillColor(sf::Color(0, 0, 0, 38));
    m_hudOutline.setOutlineThickness(-.5f);
    m_hudOutline.setOutlineColor(sf::Color(0, 0, 0, 100));
    m_hudOutline.setPosition(0, 0);
}

////////////////////////////////////////////////////////////
void HUD::update(GameState const& gameState)
{
    switch (gameState)
    {
    case GameState::GAME_RUNNING:
        break;
    case GameState::GAME_WIN:
        m_gameStateText.setString("You Won");
        break;
    case GameState::GAME_LOSE:
        m_gameStateText.setString("You Lost");
        break;
    default:
        break;
    }
}

void HUD::render(sf::RenderWindow& window)
{
    window.draw(m_hudOutline);
    window.draw(m_gameStateText);
}