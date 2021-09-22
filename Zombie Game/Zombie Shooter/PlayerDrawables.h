#pragma once
#include "CharacterCustomization.h"
#include <SFML/Graphics.hpp>
class PlayerDrawables
{
public:
	CharacterCustomization skins;


	// animation variables
	int               BASEANIMATESPEED = 6;
	static const int    SHOOTSPRITEFRAMES = 3;
	//legs animation
	int					legsMoveFrame = 0;
	int					legsMoveFrameCounter = 0;
	//shoot animation
	int					shootFrame = 0;
	int					shootFrameChangeCounter = 0;
	int					shootAnimateSpeed = 1;
	//reload animation
	int					reloadFrameChangeCounter = 0;
	int					reloadFrame = 0;
	int					reloadAnimateSpeed = 6.3;
	static const int	AMOUNTRELOADFRAMES = 19;
	//move animation
	int					moveFrame = 0;
	int					moveFrameChangeCounter = 0;
	float				animateSpeed = 6;
	static const int	AMOUNTFRAMES = 20;


	int					selectedSkin{ 1 };

	//sprite and texture variables
	sf::Texture         playerTexture;
	sf::Sprite          playerSprite;
	sf::Texture         shootingTexture;
	sf::Texture         reloadTexture;
	////player second skin
	sf::Texture         playerTexture1;
	sf::Texture         shootingTexture1;
	sf::Texture         reloadTexture1;
	////player third skin
	sf::Texture         playerTexture2;
	sf::Texture         shootingTexture2;
	sf::Texture         reloadTexture2;
	////player fourth skin
	sf::Texture         playerTexture3;
	sf::Texture         shootingTexture3;
	sf::Texture         reloadTexture3;



	sf::Sprite			legsSprite;
	sf::Texture			legsTexture;
	sf::Texture			crosshairTexture;
	sf::Sprite			crosshairSprite;
	sf::Sprite			damageSprite;
	sf::Texture			damageTexture;
	sf::Texture			bloodTrailTexture;
	sf::Sprite			bloodTrailSprite[30];

public:
	void				animateLegsWalking();
	void				animateWalking();
	void				animateReload();
	void				animateShooting(int t_ammoInMag);
	void				resetShootingAnimation();



	void loadDrawables();

};