#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <functional>

class Button
{
public:
	Button() = default;
	Button(sf::Text _text, float _outlinesize, sf::Vector2f _Position, 
		sf::Color _colortext, sf::Color _outlinecolor, std::function<int()> _f);
	~Button() = default;

	inline std::string Get_Name() { return Name; };
	inline sf::Text& Get_Texte() { return Texte; };
	inline sf::RectangleShape& Get_Shape() { return Shape; };

	inline void Set_Color(sf::Color _colortext, sf::Color _outlinecolor);
	inline void Set_ColorText(sf::Color _color) { Texte.setFillColor(_color); };
	inline void Set_ColorShape(sf::Color _color) { Shape.setOutlineColor(_color); };
	inline void Set_CallBack(std::function<int()> _f);
	inline void Set_Text(std::string _texte) { Texte.setString(_texte); }
	void Set_Position(sf::Vector2f _pos);

	int Update();
	void Display(sf::RenderWindow* _window);

private:
	sf::RectangleShape Shape;
	sf::Text Texte;
	std::string Name;

	std::function<int()> f;
};