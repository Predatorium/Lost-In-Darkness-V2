#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "State.h"
#include "Player.h"
#include <list>

class MenuDungeon : public State
{
private:
	std::list<Button> Bouton;
	sf::Font font;
	bool Arrive{ false };

public:
	MenuDungeon(State_Manager* game, sf::RenderWindow* _window, Player* joueur);
	~MenuDungeon() = default;

	void Pause() {};
	void Resume() {};

	void HandleEvents(sf::Event e);
	void Update(const float& dt);
	void Display();
};