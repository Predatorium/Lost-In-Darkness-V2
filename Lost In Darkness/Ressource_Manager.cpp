#include "Ressource_Manager.h"

Cache<sf::Texture>Ressource_Manager::m_texture;
Cache<sf::Font>Ressource_Manager::m_font;
Cache<sf::SoundBuffer>Ressource_Manager::m_sound;

template<>
std::string Ressource_Manager::CheckPath<sf::Texture>(std::string path, std::string name)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == "")
		{
			if (CheckPath<sf::Texture>(entry.path().string(), name) != "")
				return CheckPath<sf::Texture>(entry.path().string(), name);
		}

		if (entry.path().stem() == name)
		{
			if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
				return entry.path().string();
		}
	}

	return "";
}

template<>
std::string Ressource_Manager::CheckPath<sf::Font>(std::string path, std::string name)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == "")
		{
			if (CheckPath<sf::Font>(entry.path().string(), name) != "")
				return CheckPath<sf::Font>(entry.path().string(), name);
		}

		if (entry.path().stem() == name)
		{
			if (entry.path().extension() == ".ttf" || entry.path().extension() == ".otf")
				return entry.path().string();
		}
	}

	return "";
}

template<>
std::string Ressource_Manager::CheckPath<sf::SoundBuffer>(std::string path, std::string name)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().extension() == "")
		{
			if (CheckPath<sf::SoundBuffer>(entry.path().string(), name) != "")
				return CheckPath<sf::SoundBuffer>(entry.path().string(), name);
		}

		if (entry.path().stem() == name)
		{
			if (entry.path().extension() == ".wav" || entry.path().extension() == ".ogg")
				return entry.path().string();
		}
	}

	return "";
}