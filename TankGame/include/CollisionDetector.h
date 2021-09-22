#pragma once

#include <SFML/Graphics.hpp>
#include "OrientedBoundingBox.h"

/// <summary>
/// @brief Collision detection class for bounding box collisions using the Separating Axis Theorem (SAT)
///
/// @authors Nick Koirala (original version), ahnonay (SFML2 compatibility)
/// 
/// (c) 2009 - LittleMonkey Ltd
/// 
/// Hosted on github at the following URL: 
///
///https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
/// </summary>


class CollisionDetector
{
public:
	bool static collision(const sf::Sprite& object1, const sf::Sprite& object2);
};
