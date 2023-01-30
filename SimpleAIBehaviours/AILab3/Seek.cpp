#include "Seek.h"


Seek::Seek()
{
	setupSprites();
}

sf::Vector2f Seek::norm(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return { vec.x / length, vec.y / length };
}

void Seek::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (alive == true)
	{
		seek(t_deltaTime, t_player);
		nameTag.setPosition(m_seekSprite.getPosition());
	}
}

void Seek::render(sf::RenderWindow& t_window)
{
	if (alive == true)
	{
		if (tracerAlive == true)
		{
			t_window.draw(LineToPlayer);

			t_window.draw(leftLine);
			t_window.draw(rightLine);
		}
		t_window.draw(m_seekSprite);
		t_window.draw(nameTag);
	}
}



void Seek::setupSprites()
{
	if (!m_seekTexture.loadFromFile("ASSETS\\IMAGES\\seekShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_seekSprite.setTexture(m_seekTexture);
	//college pc 
	//m_m_seekSpriteSprite.setPosition(1200.0f, 500.0f);
	//m_m_seekSpriteSprite.scale(5.0f, 5.0f);
	// my pc
	m_seekSprite.setPosition(500.0f, 500.0f);
	m_seekSprite.scale(3.0f, 3.0f);
	m_seekSprite.rotate(angle);
	m_seekSprite.setOrigin(16.0f, 16.0f);
	m_seekSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	nameTag.setFont(m_font);
	nameTag.setScale(0.5f, 0.5f);
	nameTag.setString("Seek");



	leftLine.setSize({ 200,1 });
	leftLine.setFillColor(sf::Color::Green);
	rightLine.setSize({ 200,1 });
	rightLine.setFillColor(sf::Color::Green);
}

void Seek::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerpos = t_player.m_playerSprite.getPosition();
	sf::Vector2f mypos = m_seekSprite.getPosition();

	vel = playerpos - mypos; //Velocity = target.position - my.position

	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;
	float dx = mypos.x - playerpos.x;
	float dy = mypos.y - playerpos.y;
	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;
	m_seekSprite.setRotation(rotation);
	std::cout << "				Seek angle: " << rotation << std::endl;
	m_seekSprite.move(vel);
	LineToPlayer.clear();
	sf::Vertex begin{ mypos,sf::Color::Transparent };
	LineToPlayer.append(begin);
	sf::Vertex end{ playerpos, sf::Color::Red };
	LineToPlayer.append(end);



	//vision cone(same for all my npcs)
	angleOfSight = 35.0f;

	leftLine.setRotation(m_seekSprite.getRotation() - 90 - angleOfSight);
	rightLine.setRotation(m_seekSprite.getRotation() - 90 + angleOfSight);
	leftLine.setPosition(m_seekSprite.getPosition());
	rightLine.setPosition(m_seekSprite.getPosition());

	sf::Vector2f orientation = { std::cos((pi / 180) * m_seekSprite.getRotation() - 90),std::sin((pi / 180) * m_seekSprite.getRotation() - 90) };
	sf::Vector2f distance = playerpos - mypos;
	distance = norm(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);

	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((playerpos.x - mypos.x) * (playerpos.x - mypos.x) + (playerpos.y - mypos.y) * (playerpos.y - mypos.y)) <= 200.0f)
		{
			leftLine.setFillColor(sf::Color::Red);
			rightLine.setFillColor(sf::Color::Red);
		}

		else
		{
			leftLine.setFillColor(sf::Color::Yellow);
			rightLine.setFillColor(sf::Color::Yellow);
		}
	}
	else
	{
		leftLine.setFillColor(sf::Color::Yellow);
		rightLine.setFillColor(sf::Color::Yellow);
	}
}


