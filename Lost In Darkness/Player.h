#pragma once
#include "Mercenary.h"
#include "SFML/Graphics.hpp"
#include <list>

class Player
{
public :
	Player() = default;
	Player(std::list<Mercenary> _squad);
	~Player() = default;

	inline std::list<Mercenary> &Get_Squad() { return Current_Squad; };

	inline sf::Vector2f get_Position() { return Position; };

private :
	sf::Vector2f Position;
	std::list<Mercenary> Current_Squad;
	int Mercenary_Select;
};