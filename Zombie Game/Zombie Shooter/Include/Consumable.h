
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <SFML/Audio.hpp>


class Consumable
{
public:
	Consumable(float t_scale, std::string t_fileName, sf::Vector2f t_pos, std::string t_soundFileLoc) : scale(t_scale), fileName(t_fileName), position(t_pos), pickupSoundFile(t_soundFileLoc)
	{
		if (!this->consumableTexture.loadFromFile("ART/" + t_fileName))
		{
			std::cout << "error loading Consumable File" <<std::endl;
		}
		if (!this->pickupSoundBuffer.loadFromFile("resources/assets/audio/Military Voice Pack/" + t_soundFileLoc))
		{
			std::cout << "error loading Consumable File" << std::endl;
		}
		this->pickupSound.setBuffer(pickupSoundBuffer);
		this->consumableSprite.setTexture(consumableTexture);
		this->consumableSprite.setScale(sf::Vector2f(scale, scale));
		this->consumableSprite.setPosition(t_pos); 
		this->pickupSound.setVolume(33);


	};
	
	sf::Sound			pickupSound;
	sf::SoundBuffer		pickupSoundBuffer;
	virtual void        draw(sf::RenderWindow& t_window);
	virtual void        pickup(Player t_player);
	sf::Vector2f        getPosition();
	bool                active = true;
	sf::Texture         consumableTexture;
	sf::Sprite          consumableSprite;
	std::string         fileName{};
	std::string         pickupSoundFile;
	sf::Vector2f        position;
	float               scale{};
};

