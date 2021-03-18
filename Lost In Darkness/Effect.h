#pragma once
#include "Component.h"

class Effect : public Component
{
public :
	enum class Stat
	{
		Life_Point,
		Speed,
		Damage,
		Dodge,
	};

	Effect() = default;
	Effect(std::string _name, int _power, int _duration, Stat _assign);
	~Effect() = default;

	inline Stat Get_Assign() { return Assign; }
	inline int Get_Duration() { return Duration; }
	inline int Get_Power() { return Power; }

	inline void Update() { Duration--; }
	void Display(sf::RenderWindow& _window) {}

private:
	Stat Assign;
	int Duration;
	int Power;

};