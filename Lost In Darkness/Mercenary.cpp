#include "Mercenary.h"
#include "Tools.h"
#include "Ressource_Manager.h"

Mercenary::Mercenary(std::string _name, int _life, sf::Vector2i _damage, int _crit,
	int _speed, int _dodge, int _protect, Type _type, int _level)
	: Character(_name, _life, _damage, _crit, _speed, _dodge, _protect), type(_type), Level(_level)
{
	AddSkills_ByType();

	if (Level > 0)
		for (int i = 0; i < Level; i++)
			level_Up();

	Xp = 0;
	tableau_Xp[0] = 2;
	tableau_Xp[1] = 7;
	tableau_Xp[2] = 13;
	tableau_Xp[3] = 21;
	tableau_Xp[4] = 30;
}

Mercenary::Mercenary(const Mercenary& _mercenary, sf::Vector2f _position)
{
	*this = _mercenary;
	Position = _position;
}

Mercenary::Mercenary(const Mercenary& _mercenary)
{
	*this = _mercenary;
	ID++;
	Id = ID;
}

void Mercenary::AddSkills_ByType()
{
	switch (type)
	{
	case Mercenary::Type::Chevalier:
		Skills[0] = Skill("Impot", 100, Skill::Type::Ennemy, Effect());
		Skills[1] = Skill("Tranche", 80, Skill::Type::Ennemy, Effect("Saignement", -3, 2, Effect::Stat::Life_Point));
		break;
	case Mercenary::Type::Pretre:
		Skills[0] = Skill("Purification", 50, Skill::Type::Ennemy, Effect("Purification", -4, 3, Effect::Stat::Life_Point));
		Skills[1] = Skill("Soin", 0, Skill::Type::Ally, Effect("Soin", 10, 0, Effect::Stat::Life_Point));
		break;
	case Mercenary::Type::Sorcier:
		Skills[0] = Skill("Slow", 75, Skill::Type::Ennemy, Effect("Slow", 70, 2, Effect::Stat::Speed));
		Skills[1] = Skill("Motivation", 0, Skill::Type::Ally, Effect("Buff_Att", 130, 2, Effect::Stat::Damage));
		break;
	case Mercenary::Type::Assasin:
		Skills[0] = Skill("Assasinat", 120, Skill::Type::Ennemy, Effect());
		Skills[1] = Skill("Poison", 50, Skill::Type::Ennemy, Effect("Poison", -3, 3, Effect::Stat::Life_Point));
		break;
	}
}

void Mercenary::level_Up()
{
	Max_Life *= 1.15;
	Life = Max_Life;
	Damage_Save.x *= 1.15;
	Damage_Save.y *= 1.15;
	Damage = Damage_Save;
	CR_Max *= 1.15;
	Critical_Rate = CR_Max;
	Max_Speed *= 1.15;
	Speed = Max_Speed;
	Max_Dodge *= 1.15;
	Dodge = Max_Dodge;
}

void Mercenary::Update()
{

}

void Mercenary::Display_icone(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _pos)
{
	sf::RectangleShape tmp = CreateRectangle(1, { 100,100 });
	tmp.setFillColor(sf::Color::Blue);
	tmp.setPosition(_pos);

	sf::Text tmpt;
	switch (type)
	{
	case Type::Chevalier:
		tmpt = CreateText("Chevalier", _font, 15);
		break;
	case Type::Pretre:
		tmpt = CreateText("Pretre", _font, 15);
		break;
	case Type::Sorcier:
		tmpt = CreateText("Sorcier", _font, 15);
		break;
	case Type::Assasin:
		tmpt = CreateText("Assasin", _font, 15);
		break;
	}
	tmpt.setPosition(_pos);

	_window->draw(tmp);
	_window->draw(tmpt);

	if (tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
		Display_Stat(_window, Ressource_Manager::AddAnyRessources<sf::Font>("Vamp"), { _pos.x,_pos.y + 100 });
	}
}