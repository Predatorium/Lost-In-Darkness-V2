#include "Monster_Box.h"

Monster_Box::Monster_Box()
{
	My_Box[Monster::Type::Ghoul] =
		Entity::Create<Monster>("Ghoul", 20, sf::Vector2i(5, 8),
			5, 15, 10, 15, Monster::Type::Ghoul);

	My_Box[Monster::Type::Vampire] =
		Entity::Create<Monster>("Vampire", 30, sf::Vector2i(7, 12),
			15, 25, 20, 20, Monster::Type::Vampire);

	My_Box[Monster::Type::Loup_Garou] =
		Entity::Create<Monster>("Loup_Garou", 40, sf::Vector2i(11, 15),
			25, 17, 5, 35, Monster::Type::Loup_Garou);
}

Monster& Monster_Box::Get_Box(Monster::Type _find)
{
	return My_Box[_find];
}
