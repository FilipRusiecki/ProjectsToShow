#include "Zombie.h"
#include "Grid.h"

void Zombie::stopProjectile()
{
	zombieProjectile.bulletState = Bullet::State::fired;
	firingCooldown.restart();
}

void Zombie::getCell(Grid& t_grid)
{
	for (int i = 0; i < 10; i ++)
		for (int j = 9; j >= 0; j--)
		{
			{


				if (t_grid.cellGrid[i][j].cellBody.getGlobalBounds().contains(getPosition()))
				{
					cellZombieIsin = &t_grid.cellGrid[i][j];
					zombieText.setString(std::to_string(cellZombieIsin->m_id));

				}
			}
		}
}



void Zombie::turnToPlayer(sf::Vector2f t_playerPos)
{
	velocity = zombieNextMovePosition - zombieSprite.getPosition();
	thor::setLength(velocity, speed);
	zombieSprite.setRotation(thor::polarAngle(zombieNextMovePosition - zombieSprite.getPosition()));
	collisionBox.setRotation(thor::polarAngle(zombieNextMovePosition - zombieSprite.getPosition()));
}

void Zombie::processFollowPlayer(sf::Vector2f t_playerPos)
{


	turnToPlayer(t_playerPos);

}

void Zombie::processIdle(sf::Vector2f t_playerPos)
{

}





void Zombie::init(resourceHolder& t_resources)
{
	zombieAttackTexture = t_resources.getAttackTexture();
	zombieMoveTexture = t_resources.getMoveTexture();
	zombieIdleTexture = t_resources.getIdleTexture();
	zombieBreathingSound.setBuffer(t_resources.getZombieBreathingSound());
	zombieAttackSound.setBuffer(t_resources.getZombieSound());
	zombieSprite.setScale(0.47, 0.47);
	zombieSprite.setRotation(0);
	zombieSprite.setOrigin(120, 110);
	zombieProjectile.initialise(sf::Color::Green, sf::Vector2f(20, 20), 3.0f);
	collisionBox.setFillColor(sf::Color::Magenta);
	collisionBox.setSize(sf::Vector2f(80, 80));
	collisionBox.setOrigin(sf::Vector2f(80 / 2, 80 / 2));
	collisionBox.setPosition(sf::Vector2f(rand() % 1920, rand() % 1080) + sf::Vector2f(0, 20));
	zombieNextMovePosition = collisionBox.getPosition();
	zombieAttackSound.setRelativeToListener(true);
	zombieBreathingSound.setRelativeToListener(true);

	zombieText.setFont(t_resources.zombieFont);
	zombieText.setString("ERR");
	zombieAttackSound.setAttenuation(10.f);
	zombieBreathingSound.setAttenuation(10.f);
	
}

void Zombie::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
	
		t_window.draw(zombieProjectile.bulletBody);
		//t_window.draw(collisionBox);
		t_window.draw(zombieSprite);
	
	}
}

void Zombie::update(sf::Vector2f t_playerPos, int t_detectionRadius, sf::RectangleShape t_playerCollisionBox, int& t_playerHealth, Grid& t_grid, int t_cellPlayerIsIn)
{
	if (alive)
	{

	
	

		zombieText.setPosition(getPosition() - sf::Vector2f(0, 25));

		if (audioTimer.getElapsedTime() > sf::seconds(7))
		{
			zombieBreathingSound.setPosition(getPosition().x, getPosition().y, 0);
			zombieBreathingSound.setVolume(10);
			zombieBreathingSound.play();
			std::cout << "playing audio" << std::endl;
			audioTimer.restart();
		}

		zombieProjectile.update();

		


		// to avoid state switch mid attack
		if (finishedAttacking)
		{
			
			
			if (m_path.size() == 0)
			{
				goalReached = false;
			}
			//if zombie is close enough to player
			if (thor::length(t_playerPos - zombieSprite.getPosition()) <= t_detectionRadius) //if zombie is within range of player
			{
				zombieNextMovePosition = t_playerPos;                                           //just walk to the player
				currentState = State::following;
				m_path.clear();
			}
			else                                                                          //if zombie is NOT in range of player
			{
				if (!goalReached)                                      //AND if goal has not been reached by the bfs OR if the path is empty
				{
					getCell(t_grid);						
					m_path = breadthFirst(t_grid, cellZombieIsin->m_id, t_cellPlayerIsIn); //run the BFS 
				}
				else                                                                    //if goal has been reached by the bfs
				{
					{
						if (!m_path.empty() )                                          //and path is NOT empty
						{							
								zombieNextMovePosition = t_grid.at(m_path.back()).cellBody.getPosition() + sf::Vector2f(206.4,206.4);   //move the zombie to the last cell in m_back
								currentState = State::following;                                        //follow that
								if (thor::length(zombieNextMovePosition - zombieSprite.getPosition()) <= 90)     //if zombie is near enough to its goal
								{
									m_path.pop_back();                                                      //remove back cell, essentially allocating a new one to move to
									
								}		
						}
				
					}
				}
			}

			//if idling, stay in place and scan area
			

			


			if (currentState == State::following)
			{
				processFollowPlayer(t_playerPos);
			
			}


			if (collisionBox.getGlobalBounds().intersects(t_playerCollisionBox.getGlobalBounds()))
			{
				finishedAttacking = false;
				currentState = State::attacking;
			}



			if (currentState == State::attacking)
			{
				zombieAttackSound.play();
				if (t_playerCollisionBox.getGlobalBounds().intersects(this->zombieSprite.getGlobalBounds()))
				{
					std::cout << "player hit" << std::endl;
					t_playerHealth -= 1;
				}
			}


			zombieSprite.setPosition(collisionBox.getPosition());

		}




		animate();
	}

}
//////////////////////////////////
///to call for the BFS breadthFirst( passgrid, starting cell id, destination cell id)
////////////////////////////////
std::vector<int> Zombie::breadthFirst(Grid t_grid, int&  t_startCellId, int& t_destCellId)
{

	   
		getCell(t_grid);
		t_startCellId = cellZombieIsin->getID();

		t_grid.reset(); // clear the marks for all cells (m_isMarked field reset to false)
		std::queue<Cell> cellQueue;
		goalReached = false;
		cellQueue.push(t_grid.at(t_startCellId));
		
		t_grid.at(t_startCellId).setMarked(true);
		

		while (!cellQueue.empty() && !goalReached)
		{
			std::vector<Cell*>& neighbours = cellQueue.front().neighbours;
			for (int index = 0; index < neighbours.size() && !goalReached; index++)
			{
				int childCellId = neighbours.at(index)->getID();
				if (childCellId == t_destCellId)
				{
					goalReached = true;
					t_grid.at(t_destCellId).m_previousCellId = cellQueue.front().getID();
				}
				else if (t_grid.at(childCellId).isMarked() == false && t_grid.at(childCellId).m_isPassable ) // remove m_isPassable if not needed after demo
				{
					t_grid.at(childCellId).m_previousCellId = cellQueue.front().getID();
					t_grid.at(childCellId).setMarked(true);
					cellQueue.push(t_grid.at(childCellId));
				}
			}
			cellQueue.pop();


		} // end while
		std::vector<int> path;
		int cellIndex = t_destCellId;
		while (t_grid.at(cellIndex).m_previousCellId != -1)
		{
			path.push_back(cellIndex);
			cellIndex = t_grid.at(cellIndex).m_previousCellId;
		}
		path.push_back(cellIndex);
		return path;
	


}
////////////////////////////////

void Zombie::animate()
{



	if (currentState == State::following)
	{

		currentAttackFrame = 0;

		collisionBox.move(velocity);

		frameCountDown++;
		if (frameCountDown >= animateSpeed)
		{

			frameCountDown = 0;
			zombieSprite.setTexture(zombieMoveTexture);
			zombieSprite.setTextureRect(sf::IntRect((288 * currentMoveFrame), 0, 288, 311));
			currentMoveFrame++;
			if (currentMoveFrame == AMOUNTTEXTURES)
			{
				currentMoveFrame = 0;
			}
		}


	}
	

	else if (currentState == State::attacking)
	{
		//std::cout << "enemy attacks you " << std::endl;
		zombieSprite.setTexture(zombieAttackTexture);

		zombieSprite.setTextureRect(sf::IntRect(318 * currentAttackFrame, 0, 318, 294));
		attackFrameCountDown++;
		if (attackFrameCountDown == ATTACKANIMATESPEED)
		{
			attackFrameCountDown = 0;
			zombieSprite.setTextureRect(sf::IntRect(318 * currentAttackFrame, 0, 318, 294));
			currentAttackFrame++;
			{
				if (currentAttackFrame == AMOUNTATTACKTEXTURES)
				{
					finishedAttacking = true;
					currentAttackFrame = 0;
					currentState = State::following;

				}
			}
		}
	}
}



void Zombie::setPosition(sf::Vector2f t_pos)
{
	collisionBox.setPosition(t_pos);
}

sf::Vector2f Zombie::getPosition()
{
	return collisionBox.getPosition();
}
