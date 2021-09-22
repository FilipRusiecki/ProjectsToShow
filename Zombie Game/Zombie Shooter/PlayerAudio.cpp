#include "PlayerAudio.h"


void PlayerAudio::loadAudio()
{

	getHitSoundBufferVoice.loadFromFile("resources/assets/audio/Military Voice Pack/I'm Hit.wav");
	getHitSoundVoice.setBuffer(getHitSoundBufferVoice);
	reloadSoundBufferVoice.loadFromFile("resources/assets/audio/Military Voice Pack/Reload.wav");
	reloadSoundVoice.setBuffer(reloadSoundBufferVoice);
	shootSoundBuffer.loadFromFile("resources/assets/audio/Military Voice Pack/better_ak.wav");
	shootSound.setBuffer(shootSoundBuffer);
	shootSound.setVolume(2);
	outOfAmmoSoundBufferVoice.loadFromFile("resources/assets/audio/Military Voice Pack/I need Ammo.wav");
	outOfAmmoSoundVoice.setBuffer(outOfAmmoSoundBufferVoice);
	outOfAmmoSoundVoice.setVolume(33);
}



