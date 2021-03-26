#include "Monster.h"

Monster::Monster(std::string _name, int _life, sf::Vector2i _damage, 
	int _crit, int _speed, int _dodge, int _protect, Type _type)
	: Character(_name, _life, _damage, _crit, _speed, _dodge, _protect), type(_type)
{
	AddSkills_ByType();
}

Monster::Monster(const Monster& _monster, sf::Vector2f _position)
{
	*this = _monster;
	Position = _position;
}

Monster::Monster(const Monster& _monster)
{
	*this = _monster;
	ID++;
	Id = ID;
}

void Monster::AddSkills_ByType()
{
	switch (type)
	{
	case Type::Ghoul:
		Classe = "Ghoul";
		break;
	case Type::Vampire:
		Classe = "Vampire";
		break;
	case Type::Loup_Garou:
		Classe = "Loup_Garou";
		break;
	default:
		break;
	}
}
