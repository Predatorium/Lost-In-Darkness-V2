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

sf::Text CreateText(std::string _text, sf::Font& _font, unsigned charactersize)
{
	sf::Text text(_text, _font, charactersize);
	text.setOrigin(getMidle(text));
	return text;
}

sf::RectangleShape CreateRectangle(float _outlinesize , sf::Vector2f _size)
{
	sf::RectangleShape shape(_size);
	shape.setOutlineThickness(_outlinesize);
	shape.setOrigin(getMidle(shape));
	return shape;
}

float Pourcentage(int _int) 
{
	return (float)_int / 100.f;
}