#include "Game_Manager.h"
#include <exception>
#include <iostream>

Game_Manager::Game_Manager(sf::VideoMode _videomode, std::string _name, sf::Uint32 _style)
	: window(_videomode, _name, _style), state_manager(&window), Time()
{
	srand(time(NULL));
}

void Game_Manager::GameLoop()
{
	sf::Event Event;

	while (window.isOpen())
	{
		try
		{
			Time.RestartClock();

			state_manager.HandleEvents(Event);
			state_manager.Update();
			

			state_manager.Display();
		}
		catch (std::exception const& e)
		{
			std::cerr << "ERREUR : " << e.what() << std::endl;
		}
	}
}