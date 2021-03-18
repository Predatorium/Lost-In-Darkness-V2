#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>

template<typename T>
using Ressources = std::map<std::string, T*>;

class Ressource_Manager
{
private :
	static Ressources<sf::Texture> m_texture;
	static Ressources<sf::Font> m_font;

	template<typename T>
	static Ressources<T>& Get_Ressources();

public :
	Ressource_Manager() = default;
	~Ressource_Manager() = default;

	template<typename T>
	static T& AddAnyRessources(std::string _filepath)
	{
		auto it = Get_Ressources<T>().find(_filepath);

		if (it != Get_Ressources<T>().end())
			return *it->second;
		else
			std::cout << "Don t find on map texture : " << _filepath << std::endl;

		T* ressources = new T();
		if (!ressources->loadFromFile(_filepath))
			std::cout << "Don t find texture : " << _filepath << std::endl;
	
		Get_Ressources<T>().insert(std::pair<std::string, T*>(_filepath, ressources));
		return *Get_Ressources<T>().find(_filepath)->second;
	};
};

template<>
inline Ressources<sf::Texture>& Ressource_Manager::Get_Ressources()
{
	return m_texture;
}

template<>
inline Ressources<sf::Font>& Ressource_Manager::Get_Ressources()
{
	return m_font;
}