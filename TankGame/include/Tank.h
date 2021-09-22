#pragma once
#include <SFML/Graphics.hpp>
#include <MathUtility.h>
#include <algorithm>
#include "CollisionDetector.h"
#include "ProjectilePool.h"
#include <functional>

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:
    ProjectilePool m_pool;
    Tank(sf::Texture const& texture, std::vector<sf::Sprite>& m_sprites);//, sf::Vector2f const& pos);
    void update(double dt, sf::Vector2f& t_pos, std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase);
    void render(sf::RenderWindow& window);
    void increaseSpeed();
    /// <summary>
    /// @brief Decreases the speed by 1, min speed is capped at -100.
    /// 
    /// </summary>
    void decreaseSpeed();
    /// <summary>
    /// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359.
    /// 
    /// </summary>
    void increaseRotation();
    /// <summary>
    /// @brief Decreases the rotation by 1 degree, wraps to 359 degrees after 0.
    /// 
    /// </summary>
    void decreaseRotation();
    // The tank speed.
    //=========================================================================== New bullet
    // The delay time between shots in milliseconds.
    static int const s_TIME_BETWEEN_SHOTS{ 800 };

    bool m_fireRequested;

    float m_shootTimer = 10.0f;
    /// <summary>
    /// @brief Generates a request to fire a projectile.
    /// A projectile will be fired from the tip of the turret only if time limit between shots
    ///  has expired. Fire requests are not queued.
    /// </summary>
    void requestFire();





    double getTurretRotation();
    sf::Vector2f getTurretPos();
    double m_speed{ 0.0 };
    // The current rotation as applied to tank base.
    double m_rotation{ 0.0 };
    double m_turretRotation{ 0.0 };     //the current turret rotation
    double m_previousSpeed;             //previous speed of the tank
    double m_previousRotation;          //previous rotation of the tank
    double m_previousTurretRotation;    //previous rotation of the turret
    /// <summary>
  /// @brief Processes control keys and applies speed/rotation as appropriate.
  /// </summary>
    void handleKeyInput();      //function to check the key input
    void increaseTurretRotation();      //increasing the rotation of the turret
    void decreaseTurretRotation();     //decreasing the rotation of the turret
    void centreTurret();                //recentering the turret to the original position
    void adjustRotation();              //function to make the rotation better 
    void setPosition(sf::Vector2f t_pos);//m_level);
    bool m_enableRotation = true;
    std::vector<sf::Sprite>& m_wallSprites;
    sf::Texture const& m_texture;
    bool checkWallCollision();      //bool to check the collsions for the walls and the tank
    void deflect();                 // the function to push the tank of the wall
    void slowSpeed();               //function to slow the tank over time
    sf::Vector2f m_previousPosition;        //previous position for the tank
    sf::Vector2f m_position{ 500.0f,300.0f };
    sf::Vector2f getPosition() const;

    sf::Sprite getTurretSprite() const;
    sf::Sprite getBaseSprite() const;

private:
    void initSprites(); //removed const & pos 
    sf::Sprite m_tankBase;      //sprite for the tank base
    sf::Sprite m_turret;       //sprite for the tank turret          

};