#include "Tools.h"

int irandom(int Min, int Max) 
{
	return rand() % (Max - Min + 1) + Min;
}

sf::Vector2f getMidle(sf::Sprite& _o) 
{
	return sf::Vector2f(_o.getGlobalBounds().width / 2, _o.getGlobalBounds().height / 2);
}

sf::Vector2f getMidle(sf::RectangleShape& _o) 
{
	return sf::Vector2f(_o.getGlobalBounds().width / 2, _o.getGlobalBounds().height / 2);
}

sf::Vector2f getMidle(sf::Text& _o) 
{
	return sf::Vector2f(_o.getLocalBounds().left + _o.getLocalBounds().width / 2,
		_o.getLocalBounds().top + _o.getLocalBounds().height / 2);
}

sf::Text CreateText(std::string _text, sf::Font& _font, unsigned _sizeTexte)
{
	sf::Text text(_text, _font, _sizeTexte);
	return text;
}

sf::RectangleShape CreateRectangle(sf::Vector2f _size, float _outlinesize)
{
	sf::RectangleShape shape(_size);
	shape.setOutlineThickness(_outlinesize);
	return shape;
}

float Pourcentage(int _int) 
{
	return (float)_int / 100.f;
}