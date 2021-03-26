#pragma once
#include "Entity.h"
#include <list>
#include <map>
#include "Skill.h"

class Character : public Entity
{
protected:
	std::map<int, Skill> Skills;

	std::string Classe;

	int Max_Life;
	int Life;
	sf::Vector2i Damage;
	sf::Vector2i Damage_Save;
	int CR_Max;
	int Critical_Rate;
	int Max_Speed;
	int Speed;
	int Max_Dodge;
	int Dodge;

	int Protect;
	int Turn_Order;

	std::list<Effect> Current_Effect;

public :
	Character() = default;
	Character(std::string _name, int _life, sf::Vector2i _damage,
		int _crit, int _speed, int _dodge, int _protect);
	~Character() = default;

	sf::RectangleShape tmp;

	inline int Get_MaxLife() { return Max_Life; };
	inline int Get_Life() { return Life; };
	inline sf::Vector2i get_SaveDamage() { return Damage_Save; };
	inline sf::Vector2i get_Damage() { return Damage; };
	inline int Get_CRMax() { return CR_Max; };
	inline int Get_CriticalRate() { return Critical_Rate; };
	inline int Get_MaxSpeed() { return Max_Speed; };
	inline int Get_Speed() { return Speed; };
	inline int Get_MaxDodge() { return Max_Dodge; };
	inline int Get_Dodge() { return Dodge; };
	inline Skill Get_Skill(int key) { return Skills[key]; }

	inline int Get_Protect() { return Protect; };
	inline int Get_TurnOrder() { return Turn_Order; };

	inline void Res_TurnOrder() { Turn_Order = 1; };
	inline void Add_TurnOrder() { Turn_Order++; }

	int Add_Life(int _life);
	void Add_Damage(sf::Vector2i _damage);
	void Add_Speed(int _speed);
	void Add_Dodge(int _dodge);

	void Reset();
	void Restart_Stat();
	int Effect_Update();
	int Attack(Character& c, int _skill);
	int Buff(Character& c, int _skill);

	inline bool operator==(const Character& c) { return Id == c.Id; };
	inline bool operator!=(const Character& c) { return Id != c.Id; };

	void Update() {};
	void Display(sf::RenderWindow* _window) {};
	void Display(sf::RenderWindow* _window, sf::Color _color, sf::Font& _font);
	void Display_Stat(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _position);
};