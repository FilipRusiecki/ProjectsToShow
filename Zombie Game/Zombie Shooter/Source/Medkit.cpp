#include "Medkit.h"
void Medkit::pickup(Player &t_player)
{

	t_player.heal();
	active = false;
	pickupSound.play();
}

