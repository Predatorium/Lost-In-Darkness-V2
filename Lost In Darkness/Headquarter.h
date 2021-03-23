#pragma once
#include "State.h"
#include "Button.h"
#include "Merce_Box.h"
#include "Player.h"

class Headquarter : public State
{
private :
	std::list<Button> Bouton;
	std::list<Mercenary> Army;
	std::list<Button> Army_Button;
	sf::Font font;
	Merce_Box Recruitment;
	Player Joueur;

public :
	Headquarter(State_Manager* game, sf::RenderWindow* _window);
	~Headquarter() = default;

	void Pause() {};
	void Resume();

	void HandleEvents(sf::Event e);
	void Update(const float& dt);
	void Display();
};