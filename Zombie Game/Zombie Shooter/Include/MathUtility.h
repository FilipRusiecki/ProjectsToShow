#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


namespace MathUtility
{
	
	// A constant to convert from Degrees to Radians.
	double const DEG_TO_RAD = 3.14159265359 / 180.0f;

	/// <summary>
	/// @brief Returns the Euclidean distance between two points.
	/// </summary>
	/// <param name="v1">An x,y world position</param>
	/// <param name="v2">An x,y world position</param>
	/// <returns>The length of the line between v1 and v2.</returns>
	double distance(sf::Vector2f v1, sf::Vector2f v2);

	/// <summary>
	/// @brief Returns true if either of the supplied points are inside the radius of the specified circle. 
	/// </summary>
	/// <param name="ahead">The ahead vector of the tank</param>
	/// <param name="halfAhead">Assumed to be half the length of the ahead vector</param>
	/// <returns>true if either vector is inside the radius of the specified circle.</returns>
	bool lineIntersectsCircle(sf::Vector2f ahead, sf::Vector2f halfAhead, sf::CircleShape circle);

	/// <summary>
	/// @brief Truncates the supplied vector so that its length is not greater than the specified number. 
	/// If the supplied vector has a length less than the specified 
	/// ber, no truncation is performed.
	/// </summary>
	/// <param name="v">The vector to be truncated</param>
	/// <param name="max">The maximum length of the vector</param>
	/// <returns>A vector whose length is not longer than the specified maximum.</returns>
	sf::Vector2f truncate(sf::Vector2f v, float const max);

}