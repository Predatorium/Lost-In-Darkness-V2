#pragma once
#include "SFML/Graphics.hpp"

class State_Manager;

class State
{
public:
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(sf::Event e) = 0;
	virtual void Update() = 0;
	virtual void Display() = 0;

protected:
	State() = default;
	State(State_Manager* game, sf::RenderWindow* _window);
	~State() = default;

	sf::RenderWindow* window;
	State_Manager* Game;
};