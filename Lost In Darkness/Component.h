#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Component
{
protected :
	std::string Name;

public :
	Component() = default;
	Component(std::string _name);
	~Component() = default;

	inline std::string Get_Name() { return Name; };
	inline void Set_Name(std::string _name) { Name = _name; };
};