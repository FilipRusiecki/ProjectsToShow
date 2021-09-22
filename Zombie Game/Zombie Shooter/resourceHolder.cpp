#include "resourceHolder.h"





resourceHolder::resourceHolder()
{
	std::cout << "resource holder created " << std::endl;
}

sf::Texture& resourceHolder::getAttackTexture()
{
	return zombieAttackTextures;
}

sf::Texture& resourceHolder::getMoveTexture()
{
	return zombieWalkTextures;
}

sf::Texture& resourceHolder::getIdleTexture()
{
	return zombieIdleTexture;
}

sf::SoundBuffer& resourceHolder::getZombieSound()
{
	return zombieSoundBuffer;
}


sf::SoundBuffer& resourceHolder::getZombieBreathingSound()
{
	return zombieBreathingSound;
}

void resourceHolder::loadZombieSound()
{
	zombieSoundBuffer.loadFromFile("resources/assets/audio/Zombie/AttackNoise.wav");
	zombieBreathingSound.loadFromFile("resources/assets/audio/Zombie/Breathing1.wav");

	zombieFont.loadFromFile("ART/FONTS/ariblk.ttf");
}

void resourceHolder::loadZombieTexture()
{


	sf::Texture tempTexture;
	zombieAttackTextures.loadFromFile("ART/Zombie/Attack/spritesheet.png");
	std::cout << "resource holder populated with attack anims" << std::endl;





	zombieWalkTextures.loadFromFile("ART/Zombie/Move/spritesheet.png");

	std::cout << "resource holder populated with walk anims" << std::endl;



	zombieIdleTexture.loadFromFile("ART/Zombie/Idle/spritesheet.png");
	std::cout << "resource holder populated with idle anims" << std::endl;



}





