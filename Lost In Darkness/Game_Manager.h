#pragma once
#include "SFML/Graphics.hpp"
#include "State_Manager.h"
#include "Times.h"

class Game_Manager
{
private :
	sf::RenderWindow window;
	State_Manager state_manager;
	Times Time;

public :
	Game_Manager() = default;
	Game_Manager(sf::VideoMode _videomode, std::string _name, sf::Uint32 _style);
	~Game_Manager() = default;

	void GameLoop();
};