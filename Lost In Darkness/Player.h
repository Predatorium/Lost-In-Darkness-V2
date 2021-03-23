#pragma once
#include "Mercenary.h"
#include "SFML/Graphics.hpp"
#include <list>

class Player
{
public :
	Player() = default;
	~Player() = default;

	inline std::list<Mercenary*> &Get_Squad() { return Current_Squad; };
	inline void AddMercenary(Mercenary* _merce) { Current_Squad.push_back(_merce); }

	inline sf::Vector2f get_Position() { return Position; };

	void Display_Squad(sf::RenderWindow* window, sf::Font& font, sf::Vector2f pos);

private :
	sf::Vector2f Position;
	std::list<Mercenary*> Current_Squad;
};