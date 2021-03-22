#include "Headquarter.h"
#include "Ressource_Manager.h"
#include "Tools.h"
#include "State_Manager.h"
#include "Fight.h"

Headquarter::Headquarter(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	font = Ressource_Manager::AddAnyRessources<sf::Font>("../Ressources/Fonts/MetalMacabre.ttf");

	Bouton.push_back(Button(CreateText("Recrute\nChevalier", font, 20), 1, { 200, 1000 }, sf::Color::White, sf::Color::White,
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Chevalier)); return 1; }));

	Bouton.push_back(Button(CreateText("Recrute\nAssasin", font, 20), 1, { 400, 1000 }, sf::Color::White, sf::Color::White,
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Assasin)); return 1; }));

	Bouton.push_back(Button(CreateText("Recrute\nPretre", font, 20), 1, { 600, 1000 }, sf::Color::White, sf::Color::White,
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Pretre)); return 1; }));

	Bouton.push_back(Button(CreateText("Recrute\nSorcier", font, 20), 1, { 800, 1000 }, sf::Color::White, sf::Color::White,
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Sorcier)); return 1; }));

	Bouton.push_back(Button(CreateText("Dungeon", font, 40), 1, { 800, 1000 }, sf::Color::White, sf::Color::White,
		[&] { Game->PushState<Fight>(game, _window); return 1; }));
}

void Headquarter::HandleEvents(sf::Event e)
{
}

void Headquarter::Update(const float& dt)
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [](Button& b) {b.Update(); });
}

void Headquarter::Display()
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });
}
