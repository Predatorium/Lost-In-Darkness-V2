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
	void ResetEffect();
	inline void AddMercenary(Mercenary* _merce) { Current_Squad.push_back(_merce); }

	void Display_Squad(sf::RenderWindow* window, sf::Font& font, sf::Vector2f pos);

private :
	std::list<Mercenary*> Current_Squad;
};