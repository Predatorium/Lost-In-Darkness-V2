#pragma once
#include "Box.h"
#include "Mercenary.h"

class Merce_Box: public Box<Mercenary::Type, Mercenary>
{
public :
	Merce_Box();
	virtual ~Merce_Box() = default;
	Mercenary Get_Box(Mercenary::Type _find);
};