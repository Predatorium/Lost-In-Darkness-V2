#include "Game_Manager.h"
#include <exception>
#include <iostream>
#include "Menu.h"

Game_Manager::Game_Manager(sf::VideoMode _videomode, std::string _name, sf::Uint32 _style)
	: window(_videomode, _name, _style), state_manager(&window), Time()
{
	srand(time(NULL));
}

void Game_Manager::GameLoop()
{
	state_manager.PushState<Menu>(&state_manager, &window);

	while (window.isOpen()) {
		try {
			Time.RestartClock();

			for (auto e = sf::Event{}; window.pollEvent(e);) {
				state_manager.HandleEvents(e);
			}
			state_manager.Update(Time.Get_TimeDeltaF());
			
			state_manager.Display();
		}
		catch (std::exception const& e) {
			std::cerr << "ERREUR : " << e.what() << std::endl;
		}
	}
}