#pragma once
#include "Character.h"

class Monster : public Character
{
public :

	enum class Type { Ghoul, Vampire, Loup_Garou, };

	Monster() = default;
	Monster(std::string _name, int _life, sf::Vector2i _damage,
		int _crit, int _speed, int _dodge, int _protect, Type _type);

	Monster(const Monster& _monster, sf::Vector2f _position);
	Monster(const Monster& _monster);
	~Monster() = default;

	void AddSkills_ByType();

private :
	Type type;
};

