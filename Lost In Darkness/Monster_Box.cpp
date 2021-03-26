#include "Monster_Box.h"
#include "Tools.h"

Monster_Box::Monster_Box()
{
	My_Box[Monster::Type::Ghoul] =
		Entity::Create<Monster>("Ghoul", 20, sf::Vector2i(5, 8),
			5, 15, 5, 15, Monster::Type::Ghoul);

	My_Box[Monster::Type::Vampire] =
		Entity::Create<Monster>("Vampire", 30, sf::Vector2i(7, 12),
			8, 25, 10, 20, Monster::Type::Vampire);

	My_Box[Monster::Type::Loup_Garou] =
		Entity::Create<Monster>("Loup_Garou", 40, sf::Vector2i(11, 15),
			12, 17, 2, 35, Monster::Type::Loup_Garou);
}

Monster& Monster_Box::Get_Box(Monster::Type _find)
{
	return My_Box[_find];
}

Monster& Monster_Box::Rand_Box()
{
	int x = irandom(1, 20);

	if (x <= 12)
		x = 0;
	else if (x <= 18)
		x = 1;
	else
		x = 2;

	return My_Box[static_cast<Monster::Type>(x)];
}
