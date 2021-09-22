#ifndef RESOURCEHOLDER
#define RESOURCEHOLDER




#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
class resourceHolder
{
public:
    resourceHolder();

    sf::Texture& getAttackTexture();
    sf::Texture& getMoveTexture();
    sf::Texture& getIdleTexture();
    sf::SoundBuffer& getZombieSound();
    sf::SoundBuffer zombieSoundBuffer;
    sf::SoundBuffer zombieBreathingSound;
    sf::SoundBuffer& getZombieBreathingSound();
    void loadZombieSound();
    void loadZombieTexture();


    sf::Font zombieFont;

private:
    sf::Texture zombieAttackTextures;
    sf::Texture zombieWalkTextures;
    sf::Texture zombieIdleTexture;
};
#endif //!resourceManager