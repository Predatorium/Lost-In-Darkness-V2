#pragma once
#include "Component.h"
#include "Effect.h"

class Skill : public Component
{
public :
	enum class Type	{ Ally, Ennemy, };

	Skill() = default;
	Skill(std::string _name, int _percent, Type _type, Effect _effect);
	~Skill() = default;

	inline Effect Get_Effect() { return effect; }
	inline Type Get_Type() { return type; }
	inline int Get_Pourcent() { return Percentage_Damage; }

	inline bool operator==(const Skill& s) { return Name == s.Name; }
	inline bool operator!=(const Skill& s) { return Name != s.Name; }

	void Display(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _position);

private:
	int Percentage_Damage;
	Effect effect;
	Type type;

};