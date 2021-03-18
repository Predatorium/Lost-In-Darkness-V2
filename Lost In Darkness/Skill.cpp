#include "Skill.h"
#include "Ressource_Manager.h"
#include "Tools.h"

Skill::Skill(std::string _name, int _percent, Type _type, Effect _effect)
	: Component(_name), Percentage_Damage(_percent), effect(_effect), type(_type) {}

void Skill::Display(sf::RenderWindow* _window, sf::Font& _font, sf::Vector2f _position)
{
	sf::Text tLife("¨Pourcent damage : " + std::to_string(Percentage_Damage) + "%", _font, 30);
	tLife.setOrigin(getMidle(tLife));
	tLife.setPosition(_position.x, _position.y);

	sf::Text tDamage("Effect name : " + effect.Get_Name(), _font, 30);
	tDamage.setOrigin(getMidle(tDamage));
	tDamage.setPosition(_position.x, _position.y + 35);

	sf::Text target;

	if (type == Type::Ally)
		target = sf::Text("Target : Ally", _font, 30);
	else if (type == Type::Ennemy)
		target = sf::Text("Target : Ennemy", _font, 30);

	target.setOrigin(getMidle(target));
	target.setPosition(_position.x, _position.y + 70);

	sf::Text tSpeed("Effect power : " + std::to_string(effect.Get_Power()), _font, 30);
	tSpeed.setOrigin(getMidle(tSpeed));
	tSpeed.setPosition(_position.x, _position.y + 105);

	sf::Text tDodge("Effect duration : " + std::to_string(effect.Get_Duration()), _font, 30);
	tDodge.setOrigin(getMidle(tDodge));
	tDodge.setPosition(_position.x, _position.y + 140);

	_window->draw(tLife);
	_window->draw(tDamage);
	_window->draw(target);
	_window->draw(tSpeed);
	_window->draw(tDodge);
}