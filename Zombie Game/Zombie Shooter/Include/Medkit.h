#pragma once
#include "Consumable.h"
#include <SFML/Audio.hpp>
class Medkit :
	public Consumable
{
public:
	Medkit(float t_scale, std::string t_fileName, sf::Vector2f t_pos, std::string t_soundFileLoc) : Consumable(t_scale, t_fileName, t_pos, t_soundFileLoc)
	{

	};
	void pickup(Player &t_player);
private:

};

