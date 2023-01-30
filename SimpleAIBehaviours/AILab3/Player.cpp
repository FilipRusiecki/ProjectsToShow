#include "Player.h"
Player::Player()
{
	setupSprites();
}

void Player::setupSprites()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\playerShip.png"))
	{
		std::cout << "problem loading player" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);

	//college pc
	//m_playerSprite.setPosition(1800.0f, 1800.0f);
	//m_playerSprite.scale(5.0f, 5.0f);

	//my pc 
	m_playerSprite.setPosition(800.0f, 800.0f);
	m_playerSprite.scale(3.0f, 3.0f);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_playerSprite.setOrigin(16.0f, 16.0f);

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y - radiusF);


	radiusSmaller.setFillColor(sf::Color{ 121, 1, 231, 70 });
	radiusSmaller.setRadius(radiusFSmall);
	radiusSmaller.setPosition(m_playerSprite.getPosition().x - radiusFSmall, m_playerSprite.getPosition().y - radiusFSmall);


	pursuePoint.setFillColor(sf::Color{ 197, 85, 226, 80 });
	pursuePoint.setRadius(pursuePointRadius);



	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);


}

void Player::playerMovement(sf::Time& t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (speed < maxSpeedFront)
		{
			speed += 0.4;
			radiusF += 0.5f;
			radius.setRadius(radiusF);

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > maxSpeedReverse)
		{

			speed -= 0.4;
			radiusF -= 0.5f;
			radius.setRadius(radiusF);

		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		speed = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		speed = 2.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		speed = 5.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotation = m_playerSprite.getRotation();
		rotation -= 1.8;
		if (rotation == 0.0)
		{
			rotation = 359.0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotation = m_playerSprite.getRotation();
		rotation += 1.8;

		//if (rotation == 360.0)
		//{
		//	rotation = 0;
		//}
	}

	vel.x = speed * sin(m_playerSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);
	vel.y = speed * -cos(m_playerSprite.getRotation() * t_deltaTime.asMilliseconds() / 1000);
	angleInRads = (rotation - 90) * pi / 180;
	angleInRadsLeft = (rotation - 120) * pi / 180;
	angleInRadsRight = (rotation-60) * pi / 180;

	linePoint.x = m_playerSprite.getPosition().x + radiusF * cos(angleInRads);
	linePoint.y = m_playerSprite.getPosition().y + radiusF * sin(angleInRads);

	visPointLeft.x = m_playerSprite.getPosition().x + 400 * cos(angleInRadsLeft);
	visPointLeft.y = m_playerSprite.getPosition().y + 400 * sin(angleInRadsLeft);

	visPointRight.x = m_playerSprite.getPosition().x + 400 * cos(angleInRadsRight);
	visPointRight.y = m_playerSprite.getPosition().y + 400 * sin(angleInRadsRight);














	//way 1
	/*int x1 = m_playerSprite.getPosition().x;
	int y1 = m_playerSprite.getPosition().y;

	int x2 = (m_playerSprite.getPosition().x + visPointLeft.x);
	int y2 = (m_playerSprite.getPosition().y + visPointLeft.y);

	int x3 = (m_playerSprite.getPosition().x + visPointRight.x);
	int y3 = (m_playerSprite.getPosition().y + visPointRight.y);

	float areaOrig = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
	float area1 = abs((x1 - test.getPosition().x) * (y2 - test.getPosition().y) - (x2 - test.getPosition().x) * (y1 - test.getPosition().y));
	float area2 = abs((x2 - test.getPosition().x) * (y3 - test.getPosition().y) - (x3 - test.getPosition().x) * (y2 - test.getPosition().y));
	float area3 = abs((x3 - test.getPosition().x) * (y1 - test.getPosition().y) - (x1 - test.getPosition().x) * (y3 - test.getPosition().y));*/



	//float angle1 = atan2(m_playerSprite.getPosition().y - visPointLeft.y, m_playerSprite.getPosition().x - visPointLeft.x) * 180 / pi;
	//float angle2 = atan2(m_playerSprite.getPosition().y - visPointRight.y, m_playerSprite.getPosition().x - visPointRight.x) * 180 / pi;
	//sf::Vector2f targetDirection = { test.getPosition().x - m_playerSprite.getPosition().x,test.getPosition().y - m_playerSprite.getPosition().y};

	//angle = angle1 + angle2;
	//float sightAngle = angle /2;
	//float dotProduct = (targetDirection.x * sightAngle) + (targetDirection.y * sightAngle);

	
	
	//sf::Vector2f orientation = { std::cos(pi /180 * m_playerSprite.getRotation()),std::sin(pi / 180 * m_playerSprite.getRotation()) };
	//sf::Vector2f distance = test.getPosition() - m_playerSprite.getPosition();
	//sf::Vector2f normalisedVelocity = { vel.x / distance.x ,vel.y / distance.y };
	//distance = normalisedVelocity;

	//float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);

	//if (dotProduct >= 360)
	//{
	//	dotProduct = dotProduct - 360;
	//}
	//std::cout << angle << std::endl;


	////if (area1 + area2 + area3 ==areaOrig)
	//if (dotProduct > std::cos(sightAngle *2))
	//{
	//	if (sqrt((test.getPosition().x - m_playerSprite.getPosition().x) * (test.getPosition().x - m_playerSprite.getPosition().x) + (test.getPosition().y - m_playerSprite.getPosition().y) * (test.getPosition().y - m_playerSprite.getPosition().y)) <= 200.0f)
	//	{
	//		std::cout << "BRRRRR" << std::endl;
	//		sf::Vertex begin1{ m_playerSprite.getPosition(),sf::Color::Red };
	//		playerVisLeft.append(begin1);
	//		sf::Vertex end1{ visPointLeft, sf::Color::Red };
	//		playerVisLeft.append(end1);


	//		sf::Vertex begin2{ m_playerSprite.getPosition(),sf::Color::Red };
	//		playerVisRight.append(begin2);
	//		sf::Vertex end2{ visPointRight, sf::Color::Red };
	//		playerVisRight.append(end2);
	//	}
	//	else {
	//		sf::Vertex begin1{ m_playerSprite.getPosition(),sf::Color::Green };
	//		playerVisLeft.append(begin1);
	//		sf::Vertex end1{ visPointLeft, sf::Color::Cyan };
	//		playerVisLeft.append(end1);


	//		sf::Vertex begin2{ m_playerSprite.getPosition(),sf::Color::Green };
	//		playerVisRight.append(begin2);
	//		sf::Vertex end2{ visPointRight, sf::Color::Cyan };
	//		playerVisRight.append(end2);
	//	}
	//}
	//else
	//{

	//	sf::Vertex begin1{ m_playerSprite.getPosition(),sf::Color::Green };
	//	playerVisLeft.append(begin1);
	//	sf::Vertex end1{ visPointLeft, sf::Color::Cyan };
	//	playerVisLeft.append(end1);


	//	sf::Vertex begin2{ m_playerSprite.getPosition(),sf::Color::Green };
	//	playerVisRight.append(begin2);
	//	sf::Vertex end2{visPointRight, sf::Color::Cyan };
	//	playerVisRight.append(end2);
	//}












	//////////////////////////////////	//////////////////////////////////	//////////////////////////////////	//////////////////////////////////



	//////////////////////////////////
	pursuePoint.setOrigin(0, 0);
	pursuePoint.setPosition(linePoint.x - pursuePointRadius, linePoint.y- pursuePointRadius);

	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y - radiusF);
	radiusSmaller.setPosition(m_playerSprite.getPosition().x - radiusFSmall, m_playerSprite.getPosition().y - radiusFSmall);


	m_playerSprite.move(vel);
	m_playerSprite.setRotation(rotation);
	std::cout << "							player angle: " << rotation << std::endl;


}

void Player::boundry()
{

	//moving left off screen
	if (m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width)
	{
		m_playerSprite.setPosition(0 - playerOffset, m_playerSprite.getPosition().y);
	}

	//moving right of screen 
	if (m_playerSprite.getPosition().x < 0 - playerOffset)
	{
		m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width, m_playerSprite.getPosition().y);
	}

	//moving top of screen 
	if (m_playerSprite.getPosition().y < 0 - playerOffset)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, sf::VideoMode::getDesktopMode().height);
	}

	//moving bottom of screen 
	if (m_playerSprite.getPosition().y > sf::VideoMode::getDesktopMode().height)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, 0 - playerOffset);
	}


}



void Player::render(sf::RenderWindow& t_window)
{

	if (tracerAlive == true)
	{
		t_window.draw(playerLine);
		t_window.draw(playerVisLeft);
		t_window.draw(playerVisRight);
//

		t_window.draw(radius);
		t_window.draw(radiusSmaller);
		t_window.draw(pursuePoint);

	}

	t_window.draw(m_playerSprite);


}


void Player::update(sf::Time& t_deltaTime)
{
	
	boundry();
	playerLine.clear();
	playerVisLeft.clear();
	playerVisRight.clear();

	sf::Vertex begin{ m_playerSprite.getPosition(),sf::Color::Cyan };
	playerLine.append(begin);
	sf::Vertex end{ linePoint, sf::Color::Cyan };
	playerLine.append(end);

	//sf::Vertex begin1{ m_playerSprite.getPosition(),sf::Color::White };
	//playerVisLeft.append(begin1);
	//sf::Vertex end1{ visPointLeft, sf::Color::Red };
	//playerVisLeft.append(end1);


	//sf::Vertex begin2{ m_playerSprite.getPosition(),sf::Color::White };
	//playerVisRight.append(begin2);
	//sf::Vertex end2{ visPointRight, sf::Color::Red };
	//playerVisRight.append(end2);
	playerMovement(t_deltaTime);
	
}
