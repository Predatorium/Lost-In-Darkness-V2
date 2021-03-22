#ifndef CACHESYSTEM_H
#define CACHESYSTEM_H

#include <memory>
#include "SFML/Graphics.hpp"
#include <cassert>
#include <filesystem>
#include <utility>
#include "SFML/Audio.hpp"

template <typename T>
using Cache = std::map<std::string, std::unique_ptr<T>>;

namespace fs = std::filesystem;

class Ressource_Manager
{
public:

	//made my cache movable only ! 
	Ressource_Manager() = default;
	Ressource_Manager(Ressource_Manager&&) = default;
	Ressource_Manager& operator=(Ressource_Manager&&) = default;

	template<typename T>
	static T& AddAnyRessources(const std::string& filepath)// c'est sens� fixer des problemes de const char* et autres mais si ca beug remettez std::string tout seul 
	{
		auto it = getCache<T>().find(filepath);

		if (it != getCache<T>().end())
			return *it->second;
		assert(it == getCache<T>().end());


		std::string tmp = CheckPath<T>("../Ressources/", filepath);
		if (tmp != "")
			std::replace(tmp.begin(), tmp.end(), '\\', '/');
		else
			throw std::runtime_error("Failed to find mais martin est un bg" + filepath);


		std::unique_ptr<T> textureR = std::make_unique<T>();
		if (!textureR->loadFromFile(tmp))
			throw std::runtime_error("Failed to load mais greg est un bg" + filepath); //something else maybe?

		getCache<T>().insert(std::make_pair(filepath, std::move(textureR)));

		return *getCache<T>().find(filepath)->second;
	}
private:
	Ressource_Manager(Ressource_Manager const&) = delete;
	Ressource_Manager& operator=(Ressource_Manager const&) = delete;

	static Cache<sf::Texture>m_texture;
	static Cache<sf::Font>m_font;
	static Cache<sf::SoundBuffer>m_sound;

	template<typename T>
	static Cache<T>& getCache() = delete;// closing other sort of T 

	template<typename T>
	static std::string CheckPath(std::string path, std::string name) = delete;
};

template<>
inline Cache<sf::Texture>& Ressource_Manager::getCache()
{
	return m_texture;
}

template<>
inline Cache<sf::Font>& Ressource_Manager::getCache()
{
	return m_font;
}

template<>
inline Cache<sf::SoundBuffer>& Ressource_Manager::getCache()
{
	return m_sound;
}

template<>
std::string Ressource_Manager::CheckPath<sf::Texture>(std::string path, std::string name);

template<>
std::string Ressource_Manager::CheckPath<sf::Font>(std::string path, std::string name);

template<>
std::string Ressource_Manager::CheckPath<sf::SoundBuffer>(std::string path, std::string name);

#endif


