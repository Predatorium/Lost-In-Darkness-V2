#include "Merce_Box.h"

Merce_Box::Merce_Box()
{
    My_Box[Mercenary::Type::Chevalier] =
        Entity::Create<Mercenary>("Robert", 40, sf::Vector2i(8, 11), 5,
            19, 10, 30, Mercenary::Type::Chevalier, 0);

    My_Box[Mercenary::Type::Assassin] =
        Entity::Create<Mercenary>("François", 20, sf::Vector2i(17, 20), 25,
            21, 40, 15, Mercenary::Type::Assassin, 0);

    My_Box[Mercenary::Type::Pretre] =
        Entity::Create<Mercenary>("Francis", 25, sf::Vector2i(15, 20), 10,
            22, 25, 10, Mercenary::Type::Pretre, 0);

    My_Box[Mercenary::Type::Sorcier] =
        Entity::Create<Mercenary>("Roger", 30, sf::Vector2i(10, 15), 10,
            20, 20, 20, Mercenary::Type::Sorcier, 0);
}

Mercenary& Merce_Box::Get_Box(Mercenary::Type _find)
{
    return My_Box[_find];
}