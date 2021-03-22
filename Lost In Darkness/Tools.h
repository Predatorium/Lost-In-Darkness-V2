#pragma once
#include "SFML/Graphics.hpp"

int irandom(int Min, int Max);
sf::Vector2f getMidle(sf::Sprite& _o);
sf::Vector2f getMidle(sf::RectangleShape& _o);
sf::Vector2f getMidle(sf::Text& _o);

sf::Text CreateText(std::string _text, sf::Font& _font,unsigned charactersize = 30U);
sf::RectangleShape CreateRectangle(float _outlinesize = 0, sf::Vector2f _size = {0,0});

float Pourcentage(int _int);