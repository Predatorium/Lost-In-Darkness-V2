#pragma once
#include "Monster.h"
#include "Box.h"

class Monster_Box : public Box<Monster::Type, Monster>
{
public :
	Monster_Box();
	virtual ~Monster_Box() = default;
	Monster& Get_Box(Monster::Type _find);
	Monster& Rand_Box();
};