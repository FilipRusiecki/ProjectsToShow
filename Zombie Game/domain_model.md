![image](https://user-images.githubusercontent.com/58309985/115250463-83133980-a121-11eb-8624-291f80ca44b6.png)


@startuml
class Zombie
{
 void Draw();
 void Update();
 void Attack();
 void animate();
 bool alive;
 sf::sprite sprite;
 sf::rectangleShape collisionBox 
}

class GamePlay
{
sf::Sprite backgroundSprite
 void Draw();
 void Update();
 void Init();
 void checkInput();
  
}

class Menu
{
 sf::Sprite backgroundSprite
 void Draw();
 void Update();
 void Init();
 void checkInput();
  
}

class Bullet
{
 void Draw();
 void Update();
 void Fire();
  sf::sprite sprite;
 sf::rectangleShape collisionBox 
 sf::clock aliveTimer 
}
class Instructions
{
sf::Sprite backgroundSprite
 void Draw();
 void Update();
 void Init();
 void checkInput();
  
}

class Settings
{
sf::Sprite backgroundSprite
 void Draw();
 void Update();
 void Init();
 void checkInput();

}

class Player
{
 void Draw();
 void Update();
 void Init();
 void Fire();
 void getHit(int damage)
 int health
 int ammo
 sf::sprite sprite;
 sf::rectangleShape collisionBox 

}

class CollisionManager
{
  bool doesCollide(vector body1, vector body2)
}

Game *-- Zombie : Part of
Game *-- Player : Part of
Player *-- Bullet: Part of 
Game *-- CollisionManager: Part of
Game *-- GamePlay: Part of
Game *-- Menu: Part of
Game *-- Instructions: Part of
Game *-- Settings: Part of
CollisionManager*-- Bullet: Uses


CollisionManager *.. Player : Uses 
CollisionManager *.. Zombie  : Uses
@enduml
