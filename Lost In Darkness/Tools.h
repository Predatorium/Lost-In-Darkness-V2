#pragma once
#include "SFML/Graphics.hpp"

int irandom(int Min, int Max);
sf::Vector2f getMidle(sf::Sprite& _o);
sf::Vector2f getMidle(sf::RectangleShape& _o);
sf::Vector2f getMidle(sf::Text& _o);

sf::Text CreateText(std::string _text, sf::Font& _font, unsigned _sizeTexte);
sf::RectangleShape CreateRectangle(sf::Vector2f _size, float _outlinesize = 0);

float Pourcentage(int _int);