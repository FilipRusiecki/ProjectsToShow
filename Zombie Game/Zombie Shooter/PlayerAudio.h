#pragma once
#include <SFML/Audio.hpp>
class PlayerAudio
{
public:
	sf::SoundBuffer reloadSoundBufferVoice;
	sf::SoundBuffer outOfAmmoSoundBufferVoice;
	sf::SoundBuffer getHitSoundBufferVoice;
	sf::SoundBuffer shootSoundBuffer;
	sf::SoundBuffer reloadSoundOfGunBuffer;

	sf::Sound reloadSoundVoice;
	sf::Sound outOfAmmoSoundVoice;
	sf::Sound getHitSoundVoice;
	sf::Sound shootSound;
	sf::Sound reloadSoundGun;

	void loadAudio();
};