#include "Character.h"
#include "Tools.h"

Character::Character(std::string _name, int _life, sf::Vector2i _damage,
	int _crit, int _speed, int _dodge, int _protect)
	: Entity(_name)
{
	Life = _life;
	Max_Life = Life;
	Speed = _speed;
	Max_Speed = Speed;
	Dodge = _dodge;
	Max_Dodge = Dodge;
	Critical_Rate = _crit;
	CR_Max = Critical_Rate;
	Damage = _damage;
	Damage_Save = Damage;
	Protect = _protect;
	Turn_Order = 1;

	tmp = sf::RectangleShape(sf::Vector2f(100, 200));
	tmp.setOrigin(getMidle(tmp));
	tmp.setOutlineThickness(2);
	tmp.setOutlineColor(sf::Color(150, 150, 150, 255));
}

int Character::Add_Life(int _life)
{
	if (Life + _life > Max_Life)
	{
		int tmp = Life;
		Life = Max_Life;
		return Max_Life - tmp;
	}
	else if (Life + _life < 0)
	{
		int tmp = Life;
		Life = 0;
		return Life;
	}
	else
	{
		Life += _life;
		return _life;
	}
}

void Character::Add_Damage(sf::Vector2i _damage)
{
	Damage += _damage - Damage_Save;
}

void Character::Add_Speed(int _speed)
{
	Speed += _speed - Max_Speed;
}

void Character::Add_Dodge(int _dodge)
{
	if (Dodge > Max_Dodge)
	{
		Dodge = Max_Dodge;
		Dodge += _dodge;
	}
	else
		Dodge += _dodge;
}

void Character::Reset()
{
	Restart_Stat();
	Current_Effect.clear();
	Life = Max_Life;
}

void Character::Restart_Stat()
{
	Speed = Max_Speed;
	Dodge = Max_Dodge;
	Damage = Damage_Save;
}

int Character::Effect_Update()
{
	Restart_Stat();
	int affiche = 0;

	for (Effect& Current : Current_Effect)
	{
		if (Current.Get_Assign() == Effect::Stat::Life_Point)
			affiche += Add_Life(Current.Get_Power());
		if (Current.Get_Assign() == Effect::Stat::Damage)
			Add_Damage(sf::Vector2i(get_SaveDamage().x * Pourcentage(Current.Get_Power()),
				get_SaveDamage().y * Pourcentage(Current.Get_Power())));
		if (Current.Get_Assign() == Effect::Stat::Speed)
			Add_Speed(Get_MaxSpeed() * Pourcentage(Current.Get_Power()));
		if (Current.Get_Assign() == Effect::Stat::Dodge)
			Add_Dodge(Get_MaxDodge() * Pourcentage(Current.Get_Power()));

		if (Current.Get_Duration() > 0)
			Current.Update();
	}

	Current_Effect.remove_if([](Effect& e) {return e.Get_Duration() == 0; });

	return affiche;
}

int Character::Attack(Character& c, int _skill)
{
	int dodge = irandom(0, 100);

	if (dodge <= Dodge)
		return 0;

	if (Skills[_skill] != Skill()) {
		c.Current_Effect.push_back(Skills[_skill].Get_Effect());
		if (Skills[_skill].Get_Effect().Get_Assign() == Effect::Stat::Speed)
			c.Add_Speed(Get_MaxSpeed() * Pourcentage(Skills[_skill].Get_Effect().Get_Power()));
	}

	int rand = irandom(Damage.x, Damage.y);
	if (Skills[_skill] != Skill())
		rand *= Pourcentage(Skills[_skill].Get_Pourcent());
	rand *= 1.f - Pourcentage(c.Protect);

	int RandCrit = irandom(0, 100);

	if (RandCrit <= Critical_Rate)
		rand *= 2;

	return c.Add_Life(-rand);
}

int Character::Buff(Character& c, int _skill)
{
	if (Skills[_skill].Get_Effect().Get_Duration() > 0)
		c.Current_Effect.push_back(Skills[_skill].Get_Effect());

	int affiche = 0;

	if (Skills[_skill].Get_Effect().Get_Assign() == Effect::Stat::Life_Point)
		affiche += c.Add_Life(Skills[_skill].Get_Effect().Get_Power());
	if (Skills[_skill].Get_Effect().Get_Assign() == Effect::Stat::Damage)
		c.Add_Damage(sf::Vector2i(c.get_SaveDamage().x * Pourcentage(Skills[_skill].Get_Effect().Get_Power()),
			c.get_SaveDamage().y * Pourcentage(Skills[_skill].Get_Effect().Get_Power())));
	if (Skills[_skill].Get_Effect().Get_Assign() == Effect::Stat::Speed)
		c.Add_Speed(Get_MaxSpeed() * Pourcentage(Skills[_skill].Get_Effect().Get_Power()));
	if (Skills[_skill].Get_Effect().Get_Assign() == Effect::Stat::Dodge)
		c.Add_Dodge(Get_MaxDodge() * Pourcentage(Skills[_skill].Get_Effect().Get_Power()));

	return affiche;
}

void Character::Display(sf::RenderWindow* _window, sf::Color _color, sf::Font& _font)
{
	tmp.setFillColor(_color);

	sf::Text tClasse = CreateText(Classe, _font);
	tClasse.setPosition(Position);
	tClasse.setFillColor(sf::Color(100,100,100));

	sf::RectangleShape life_Box(sf::Vector2f(100, 20));
	life_Box.setFillColor(sf::Color::Transparent);
	life_Box.setOutlineThickness(2);
	life_Box.setOutlineColor(sf::Color::White);

	sf::RectangleShape life(sf::Vector2f(life_Box.getSize().x / Max_Life * Life, 20));
	life.setFillColor(sf::Color::Red);

	life_Box.setPosition(Position.x - tmp.getSize().x / 2, Position.y + 110);
	life.setPosition(Position.x - tmp.getSize().x / 2, Position.y + 110);
	tmp.setPosition(Position);

	_window->draw(life_Box);
	_window->draw(life);
	_window->draw(tmp);
	_window->draw(tClasse);
}

void Character::Display_Stat(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _position)
{
	sf::Text tName(Name, _font, 35);
	tName.setOrigin(getMidle(tName));
	tName.setPosition(_position.x, _position.y);

	sf::Text tLife("Life : " + std::to_string(Life) + "/" + std::to_string(Max_Life), _font, 30);
	tLife.setOrigin(getMidle(tLife));
	tLife.setPosition(_position.x, _position.y + 35);

	sf::Text tDamage("Damage : " + std::to_string(Damage.x) + "-" + std::to_string(Damage.y), _font, 30);
	tDamage.setOrigin(getMidle(tDamage));
	tDamage.setPosition(_position.x, _position.y + 70);

	sf::Text tCrit("Crit : " + std::to_string(Critical_Rate), _font, 30);
	tCrit.setOrigin(getMidle(tCrit));
	tCrit.setPosition(_position.x, _position.y + 105);

	sf::Text tSpeed("Speed : " + std::to_string(Speed), _font, 30);
	tSpeed.setOrigin(getMidle(tSpeed));
	tSpeed.setPosition(_position.x, _position.y + 140);

	sf::Text tDodge("Dodge : " + std::to_string(Dodge), _font, 30);
	tDodge.setOrigin(getMidle(tDodge));
	tDodge.setPosition(_position.x, _position.y + 175);

	sf::Text tProtect("Protect : " + std::to_string(Protect), _font, 30);
	tProtect.setOrigin(getMidle(tProtect));
	tProtect.setPosition(_position.x, _position.y + 210);

	_window->draw(tName);
	_window->draw(tLife);
	_window->draw(tDamage);
	_window->draw(tCrit);
	_window->draw(tSpeed);
	_window->draw(tDodge);
	_window->draw(tProtect);
}