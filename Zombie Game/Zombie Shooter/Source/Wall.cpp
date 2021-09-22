#include "Wall.h"

//all of the collisions are absolute garbage code but FUNCTIONAL garbage code
//NEED REFACTOR FOR ENTIRE CLASS


void Wall::checkCollisionsWithPlayer(Player& t_player)
{


	if (t_player.collisionBox.getGlobalBounds().intersects(body.getGlobalBounds()))
	{

		t_player.canMove = false;
		t_player.setPosition(lastKnownPlayerPos);


		if (body.getSize().x > body.getSize().y)
		{
			if (t_player.collisionBox.getPosition().y < body.getPosition().y)
			{
				t_player.setPosition(t_player.getPosition() - sf::Vector2f(0, 2));
			}
			if (t_player.collisionBox.getPosition().y > body.getPosition().y)
			{
				t_player.setPosition(t_player.getPosition() + sf::Vector2f(0, 2));
			}
		}



		if (body.getSize().y > body.getSize().x)
		{
			if (t_player.collisionBox.getPosition().x < body.getPosition().x)
			{
				t_player.setPosition(t_player.getPosition() - sf::Vector2f(2, 0));
			}
			if (t_player.collisionBox.getPosition().x > body.getPosition().x)
			{
				t_player.setPosition(t_player.getPosition() + sf::Vector2f(2, 0));
			}
		}

		if (body.getSize().y == body.getSize().x)
		{
			std::cout << "do this later" << std::endl;
			sf::Vector2f lineBetween = t_player.getPosition() - this->body.getPosition();
			thor::setLength(lineBetween, 2.0f);
			

			t_player.setPosition(t_player.getPosition() + lineBetween);
			


		}
	}
	else
	{

		t_player.canMove = true;
	}

	lastKnownPlayerPos = t_player.getPosition();


	for (int i = 0; i < t_player.MAXAMMOPERMAG; i++)
	{
		if (t_player.bullet[i].bulletState == Bullet::State::moving)
		{
			if (t_player.bullet[i].bulletBody.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				t_player.bullet[i].bulletState = Bullet::State::fired;
			}
		}
	}

}

void Wall::checkCollisionsWithEnemy(Zombie& t_zombie)
{
	lastKnownZombiePos = t_zombie.getPosition();
	if (t_zombie.collisionBox.getGlobalBounds().intersects(body.getGlobalBounds()))
	{


		t_zombie.setPosition(lastKnownZombiePos);

		if (t_zombie.collisionBox.getPosition().x < body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() - sf::Vector2f(2, 0));
		}
		if (t_zombie.collisionBox.getPosition().x > body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() + sf::Vector2f(2, 0));
		}


		if (t_zombie.collisionBox.getPosition().y < body.getPosition().y)
		{
			t_zombie.setPosition(t_zombie.getPosition() - sf::Vector2f(0, 2));
		}
		if (t_zombie.collisionBox.getPosition().y > body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() + sf::Vector2f(0, 2));
		}
		t_zombie.zombieNextMovePosition = lastKnownZombiePos;
	}





}




void Wall::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}
