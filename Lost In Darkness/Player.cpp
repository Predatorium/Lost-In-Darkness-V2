#include "Player.h"

void Player::Display_Squad(sf::RenderWindow* window, sf::Font& font, sf::Vector2f pos)
{
	int i = 0;
	for (auto& Current : Current_Squad) {
		Current->Display_icone(window, font, { pos.x - (i * 200), pos.y });
		i++;
	}
}
