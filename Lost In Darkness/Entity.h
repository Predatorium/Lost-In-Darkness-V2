#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Entity
{
protected :
	std::string Name;
	sf::Sprite sprite;
	sf::Vector2f Position;
	int Id;

public :
	Entity() = default;
	Entity(std::string _name);
	~Entity();

	template <typename T, class ... Args>
	static T Create(Args&& ...args) { return T(std::forward<Args>(args)...); }

	template <typename T>
	T Clone() { return T(*this); }

	inline sf::Vector2f Get_Position() { return Position; }
	inline std::string Get_Name() { return Name; }
	inline sf::Sprite Get_Sprite() { return sprite; }

	inline void Set_Position(float _x, float _y) { Position = sf::Vector2f(_x, _y); sprite.setPosition(Position); }
	inline void Set_Position(sf::Vector2f _position) { Position = _position; sprite.setPosition(Position); }
	inline void Set_Name(std::string _name) { Name = _name; }

	inline void Add_Position(float _x, float _y) { Position.x += _x; Position.y += _y; sprite.setPosition(Position); }

	virtual void Update() = 0;
	virtual void Display(sf::RenderWindow* _window) = 0;
};