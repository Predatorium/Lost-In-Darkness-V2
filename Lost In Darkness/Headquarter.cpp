#include "Headquarter.h"
#include "Ressource_Manager.h"
#include "Tools.h"
#include "State_Manager.h"
#include "Fight.h"

Headquarter::Headquarter(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	font = Ressource_Manager::AddAnyRessources<sf::Font>("MetalMacabre");

	Bouton.push_back(Button(CreateText("Recrute\nChevalier", font, 20), CreateRectangle(1.f), { 200, 390 },
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Chevalier)); }));

	Bouton.push_back(Button(CreateText("Recrute\nAssasin", font, 20), CreateRectangle(1.f), { 200, 490 },
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Assasin)); }));

	Bouton.push_back(Button(CreateText("Recrute\nPretre", font, 20), CreateRectangle(1.f), { 200, 590 },
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Pretre)); }));

	Bouton.push_back(Button(CreateText("Recrute\nSorcier", font, 20), CreateRectangle(1.f), { 200, 690 },
		[&] {Army.push_back(Recruitment.Get_Box(Mercenary::Type::Sorcier)); }));

	Bouton.push_back(Button(CreateText("Dungeon", font, 40), CreateRectangle(1.f), { 960, 1000 },
		[this] { Game->PushState<Fight>(Game, window); }));
}

void Headquarter::HandleEvents(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::KeyPressed:
		switch (e.key.code)
		{
		case sf::Keyboard::Key::Escape:
			Game->PopState();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Headquarter::Update(const float& dt)
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [](Button& b) {b.Update(); });
}

void Headquarter::Display()
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });
}
