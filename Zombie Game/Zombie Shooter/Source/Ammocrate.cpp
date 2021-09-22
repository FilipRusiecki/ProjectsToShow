#include "Ammocrate.h"

void Ammocrate::pickup(Player& t_player)
{
	t_player.pickupAmmo(23);
	active = false;
	pickupSound.play();


}

