#pragma once

#include <SFML/Graphics.hpp>

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

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox(const sf::Sprite& Object); // Calculate the four points of the OBB from a transformed (scaled, rotated...) RectangleShape

	sf::Vector2f Points[4];

	void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max); // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
};
