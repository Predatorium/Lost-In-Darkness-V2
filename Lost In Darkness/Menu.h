#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "State.h"
#include <list>

class Menu : public State
{
private :
	std::list<Button> Bouton;
	Button Title;
	sf::Font font;
	sf::Sprite sprite;
	float timer;
	int Selection;

public :
	Menu(State_Manager* game, sf::RenderWindow* _window);
	~Menu() = default;

	void Pause() {};
	void Resume() {};

	void HandleEvents(sf::Event e);
	void Update();
	void Display();
};