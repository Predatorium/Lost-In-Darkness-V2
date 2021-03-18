#include "Effect.h"

Effect::Effect(std::string _name, int _power, int _duration, Stat _assign)
{
	Name = _name;
	Power = _power;
	Duration = _duration;
	Assign = _assign;
}