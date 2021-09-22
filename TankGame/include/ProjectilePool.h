#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Projectile.h"
#include <functional>

class ProjectilePool
{
public:

	/// <summary>
	/// @brief No-op default constructor
	/// </summary>
	ProjectilePool() = default;

	/// <summary>
	/// @brief Creates a projectile.
	/// Creates a projectile from the pool of available projectiles.
	///  If no projectiles are available, the next in (pool) sequence after
	///  the last used projectile is chosen.
	/// </summary>
	/// <param name="texture">A reference to the sprite sheet texture</param>	
	/// <param name="x">The x position of the projectile</param>
	/// <param name="x">The y position of the projectile</param>
	/// <param name="rotation">The rotation angle of the projectile in degrees</param>
	void create(sf::Texture const & texture, double x, double y, double rotation);

	/// <summary>
	/// @brief Updates all projectiles in the pool.
	/// Sets an index to the next available projectile. Also sets a 
	///  status flag to indicate pool full (all projectiles in use).
	/// </summary>
	/// <param name="dt">The delta time</param>	
	/// <param name="rotation">A reference to the container of wall sprites</param>
	void update(double dt, std::vector<sf::Sprite> & wallSprites, std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase);

	/// <summary>
	/// @brief Draws all active projectiles.
	/// </summary>
	/// <param name="window">The SFML render window</param>	
	void render(sf::RenderWindow & window);


private:
	static const int s_POOL_SIZE = 100;

	// A container for the projectiles.
	std::array<Projectile, s_POOL_SIZE> m_projectiles;

	// The index of the next available projectile.
	int m_nextAvailable { 0 };

	// A flag indicating whether there are any projectiles available (initially they are).
	bool m_poolFull { false };
};