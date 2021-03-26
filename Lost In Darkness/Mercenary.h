#pragma once
#include "Character.h"

class Mercenary : public Character
{
public :
	enum class Type { Chevalier, Pretre, Sorcier, Assassin, };

	Mercenary() = default;
	Mercenary(std::string _name, int _life, sf::Vector2i _damage, int _crit,
		int _speed, int _dodge, int _protect, Type _type, int _level);
	Mercenary(const Mercenary& _mercenary, sf::Vector2f _position);
	Mercenary(const Mercenary& _mercenary);
	~Mercenary() = default;

	Type Get_Type() { return type; }

	void AddSkills_ByType();
	void level_Up();
	void Display_icone(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _pos);

private :
	Type type;
	int Level;
	int tableau_Xp[5];
	int Xp;
};