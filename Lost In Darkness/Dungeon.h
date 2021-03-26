#pragma once
#include "State.h"
#include "Room.h"
#include "Player.h"
#include <vector>
#include "Button.h"

class Dungeon : public State
{
private:
	Player* player;
	std::vector<Room> Salle;
	int CurrentRoom{ 0 };
	sf::Font font;
	Button Back;
	Button Next;

public:
	Dungeon(State_Manager* game,
		sf::RenderWindow* _window, Player* joueur);
	~Dungeon() { ; }

	void Pause() { ; }
	void Resume();

	void HandleEvents(sf::Event e);
	void Update(const float& dt);
	void Display();
};