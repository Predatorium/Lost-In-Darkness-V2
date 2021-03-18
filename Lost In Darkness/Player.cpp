#include "Player.h"

Player::Player(std::list<Mercenary> _squad)
{
	Current_Squad.clear();
	for (Mercenary& Current : _squad)
		Current_Squad.push_back(Current);

	Mercenary_Select = 0;
}