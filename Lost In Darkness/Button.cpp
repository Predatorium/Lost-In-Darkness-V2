#include "Button.h"
#include "Tools.h"

Button::Button(sf::Text _text, float _outlinesize,	sf::Vector2f _Position, 
	sf::Color _colortext, sf::Color _outlinecolor, std::function<int()> _f)
	: Name(_text.getString()), Texte(_text)
{
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(sf::Vector2f(_Position));
	Texte.setFillColor(_colortext);

	Shape = sf::RectangleShape(sf::Vector2f(Texte.getLocalBounds().width,
		Texte.getLocalBounds().height));
	Shape.setOrigin(getMidle(Shape));
	Shape.setPosition(_Position);
	Shape.setFillColor(sf::Color::Transparent);
	Shape.setOutlineThickness(_outlinesize);
	Shape.setOutlineColor(_outlinecolor);

	f = _f;
}

void Button::Set_Color(sf::Color _colortext, sf::Color _outlinecolor)
{
	Texte.setFillColor(_colortext);
	Shape.setOutlineColor(_outlinecolor);
}

void Button::Set_CallBack(std::function<int()> _f)
{
	f = _f;
}

void Button::Set_Position(sf::Vector2f _pos)
{
	Texte.setOrigin(getMidle(Texte));
	Texte.setPosition(_pos);
	Shape.setSize(sf::Vector2f(Texte.getLocalBounds().width,
		Texte.getLocalBounds().height));
	Shape.setOrigin(getMidle(Shape));
	Shape.setPosition(_pos);
}

int Button::Update()
{
	return f();
}

void Button::Display(sf::RenderWindow* _window)
{
	_window->draw(Texte);
	_window->draw(Shape);
}