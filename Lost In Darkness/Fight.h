#pragma once
#include "State.h"
#include "Player.h"
#include "Button.h"
#include "Monster.h"
#include "Times.h"
#include <list>
#include "Merce_Box.h"

class Fight : public State
{
private :
	Player player;
	std::list <Button> Bouton;
	std::list<Monster> Enemy;
	sf::Font font;
	sf::Sprite sprite;
	float timer;
	int Enemy_Selection;
	int turn;
	int Skill_Select;
	bool EffectUpdate;

	Merce_Box m_Box;

	enum class Etape
	{
		Attack,
		AfDamage,
	};
	Etape etape;

public :
	Fight(State_Manager* game, sf::RenderWindow* _window);
	~Fight() = default;

	void Turn_Order();

	void Pause() {};
	void Resume() {};

	void HandleEvents(sf::Event e);
	void Update();
	void Display();
};