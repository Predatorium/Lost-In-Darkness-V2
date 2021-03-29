#pragma once
#include "State.h"
#include "Player.h"
#include "Button.h"
#include <list>
#include "Merce_Box.h"
#include "Monster_Box.h"

class Fight : public State
{
private :
	Player* player{ nullptr };
	std::list<Button> Bouton;
	std::list<Monster> Enemy;
	sf::Font font;
	float timer{ 0.f };
	int Enemy_Selection{ 0 };
	int turn{ 1 };
	int Skill_Select{ -1 };
	bool EffectUpdate{ false };

	Monster_Box Mo_Box;

	enum class Etape { Attack, AfDamage, };
	Etape etape{ Etape::Attack };

public :
	Fight(State_Manager* game, sf::RenderWindow* _window, Player* joueur);
	~Fight() { ; }

	void Turn_Order();

	void Pause() { ; }
	void Resume() { ; }

	void HandleEvents(sf::Event e);
	void Update(const float& dt);
	void Display();
};