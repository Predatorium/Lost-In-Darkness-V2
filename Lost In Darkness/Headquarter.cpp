#include "Headquarter.h"
#include "Ressource_Manager.h"
#include "Tools.h"
#include "State_Manager.h"
#include "Dungeon.h"

Headquarter::Headquarter(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	font = Ressource_Manager::AddAnyRessources<sf::Font>("MetalMacabre");

	Bouton.push_back(Button(CreateText("Recrute\nChevalier", font, 20), CreateRectangle(1.f), { 100, 390 },
		[this] {
			if (Army.size() < 12) {
				Army.push_back(Mercenary(Recruitment.Get_Box(Mercenary::Type::Chevalier)));
				auto* it = &Army.back();
				Army_Button.push_back(Button(CreateText("Chevalier", font, 20),
					CreateRectangle(1.f, { 120,50 }), sf::Color::Blue, sf::Vector2f(1800, 60 * Army.size()), [this, it] {
						if (Joueur.Get_Squad().size() < 4) {
							bool find = false;
							for (auto& current : Joueur.Get_Squad())
								if (current == it)
									find = true;

							if (!find)
								Joueur.AddMercenary(it);
						}
					}));
			}
		}));

	Bouton.push_back(Button(CreateText("Recrute\nAssasin", font, 20), CreateRectangle(1.f), { 100, 490 },
		[this] {
			if (Army.size() < 12) {
				Army.push_back(Mercenary(Recruitment.Get_Box(Mercenary::Type::Assassin)));
				auto* it = &Army.back();
				Army_Button.push_back(Button(CreateText("Assasin", font, 20),
					CreateRectangle(1.f, { 120,50 }), sf::Color::Blue, sf::Vector2f(1800, 60 * Army.size()), [this, it] {
						if (Joueur.Get_Squad().size() < 4) {
							bool find = false;
							for (auto& current : Joueur.Get_Squad())
								if (current == it)
									find = true;

							if (!find)
								Joueur.AddMercenary(it);
						}
					}));
			}
		}));

	Bouton.push_back(Button(CreateText("Recrute\nPretre", font, 20), CreateRectangle(1.f), { 100, 590 },
		[this] {
			if (Army.size() < 12) {
				Army.push_back(Mercenary(Recruitment.Get_Box(Mercenary::Type::Pretre)));
				auto* it = &Army.back();
				Army_Button.push_back(Button(CreateText("Pretre", font, 20),
					CreateRectangle(1.f, { 120,50 }), sf::Color::Blue, sf::Vector2f(1800, 60 * Army.size()), [this, it] {
						if (Joueur.Get_Squad().size() < 4) {
							bool find = false;
							for (auto& current : Joueur.Get_Squad())
								if (current == it)
									find = true;

							if (!find)
								Joueur.AddMercenary(it);
						}
					}));
			}
		}));

	Bouton.push_back(Button(CreateText("Recrute\nSorcier", font, 20), CreateRectangle(1.f), { 100, 690 },
		[this] {
			if (Army.size() < 12) {
				Army.push_back(Mercenary(Recruitment.Get_Box(Mercenary::Type::Sorcier)));
				auto* it = &Army.back();
				Army_Button.push_back(Button(CreateText("Sorcier", font, 20),
					CreateRectangle(1.f, { 120,50 }), sf::Color::Blue, sf::Vector2f(1800, 60 * Army.size()), [this, it] {
						if (Joueur.Get_Squad().size() < 4) {
							bool find = false;
							for (auto& current : Joueur.Get_Squad())
								if (current == it)
									find = true;

							if (!find)
								Joueur.AddMercenary(it);
						}
					}));
			}
		}));

	Bouton.push_back(Button(CreateText("Clear\nSquad", font, 20), CreateRectangle(1.f), { 50, 50 },
		[this] {
			Joueur.Get_Squad().clear();
		}));

	Bouton.push_back(Button(CreateText("Dungeon", font, 40), CreateRectangle(1.f), { 960, 1040 },
		[this] {
			if (Joueur.Get_Squad().size() >= 2) {
				Game->PushState<Dungeon>(Game, window, &Joueur);
			}
		}));
}

void Headquarter::Resume()
{
	Army.remove_if([](Mercenary& value) {
		return value.Get_Life() == 0;
		});

	Army_Button.clear();

	int i = 1;
	for (Mercenary& Current : Army) {
		auto* it = &Current;
		std::string tmp;
		if (Current.Get_Type() == Mercenary::Type::Assassin)
			tmp = "Assassin";
		if (Current.Get_Type() == Mercenary::Type::Chevalier)
			tmp = "Chevalier";
		if (Current.Get_Type() == Mercenary::Type::Pretre)
			tmp = "Pretre";
		if (Current.Get_Type() == Mercenary::Type::Sorcier)
			tmp = "Sorcier";

		Army_Button.push_back(Button(CreateText(tmp, font, 20),
			CreateRectangle(1.f, { 100,100 }), sf::Vector2f(1800, 50 * i), [this, it] {
				if (Joueur.Get_Squad().size() < 4)
					Joueur.AddMercenary(it);
			}));
		i++;
	}
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
	for (auto it = std::begin(Bouton); it != std::end(Bouton); it++) {
		if (it->Update()) {
			break;
		}
	}
	for (auto it = std::begin(Army_Button); it != std::end(Army_Button); it++) {
		if (it->Update()) {
			break;
		}
	}
}

void Headquarter::Display()
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });
	std::for_each(std::begin(Army_Button), std::end(Army_Button), [this](Button& b) {b.Display(window); });
	Joueur.Display_Squad(window, font, { 1260, 200 });
}