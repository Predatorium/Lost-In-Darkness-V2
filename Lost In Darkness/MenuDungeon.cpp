#include "MenuDungeon.h"
#include "Ressource_Manager.h"
#include "State_Manager.h"
#include "Tools.h"
#include "Dungeon.h"

MenuDungeon::MenuDungeon(State_Manager* game, sf::RenderWindow* _window, Player* joueur) : State(game, _window)
{
	font = Ressource_Manager::AddAnyRessources<sf::Font>("MetalMacabre");

	Bouton.push_back(Button(CreateText("Easy", font, 70), CreateRectangle(1.f, { 300,70 }), 
		sf::Color(150, 150, 150), { 480, 540 },
		[this, joueur] {Game->ChangeState<Dungeon>(Game, window, joueur, 1); }));

	Bouton.push_back(Button(CreateText("Normal", font, 70), CreateRectangle(1.f, { 300,70 }), 
		sf::Color(150, 150, 150), {960, 540},
		[this, joueur] {Game->ChangeState<Dungeon>(Game, window, joueur, 2); }));

	Bouton.push_back(Button(CreateText("Hard", font, 70), CreateRectangle(1.f, { 300,70 }), 
		sf::Color(150, 150, 150), { 1440, 540 },
		[this, joueur] {Game->ChangeState<Dungeon>(Game, window, joueur, 3); }));

	Bouton.push_back(Button(CreateText("HeadQuarter", font, 70), CreateRectangle(1.f, { 450,70 }),
		sf::Color(150, 150, 150), { 960, 1040 },
		[this] {Game->PopState(); }));
}

void MenuDungeon::HandleEvents(sf::Event e)
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

void MenuDungeon::Update(const float& dt)
{
	if (Arrive) {
		for (auto it = std::begin(Bouton); it != std::end(Bouton); it++) {
			if (it->Update()) {
				break;
			}
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Arrive = true;
	}
}

void MenuDungeon::Display()
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });
}
