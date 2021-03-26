#include "Dungeon.h"
#include "Tools.h"
#include "Ressource_Manager.h"
#include "Fight.h"
#include "State_Manager.h"

Dungeon::Dungeon(State_Manager* game, sf::RenderWindow* _window, Player* joueur) : State(game, _window), player(joueur)
{
	font = Ressource_Manager::AddAnyRessources<sf::Font>("Vamp");
	Back = Button(CreateText("Back", font), CreateRectangle(1, { 75,50 }), sf::Color::Blue,
		{ 200,480 }, [this] { if (CurrentRoom > 0) CurrentRoom--; });
	Next = Button(CreateText("Next", font), CreateRectangle(1, { 75,50 }), sf::Color::Blue,
		{ 1720,480 }, [this] { if (CurrentRoom < Salle.size()) CurrentRoom++; });

	int i = 1;
	for (auto Current : player->Get_Squad()) {
		Current->Set_Position(960.f - (200.f * i), 665.f);
		i++;
	}

	int rand = irandom(5, 7);
	for (int x = 0; x < rand; x++) {
		int rand2 = irandom(1, 2);
		Salle.push_back(Room(static_cast<Room::Event>(rand2 - 1)));
	}
}

void Dungeon::Resume()
{
	int i = 1;
	for (auto Current : player->Get_Squad()) {
		Current->Set_Position(960.f - (200.f * i), 665.f);
		i++;
	}

	Salle[CurrentRoom].Win();
}

void Dungeon::HandleEvents(sf::Event e)
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

	if (player->Get_Squad().size() == 0)
		Game->PopState();
}

void Dungeon::Update(const float& dt)
{
	Back.Update();
	Next.Update();

	if (CurrentRoom < Salle.size()) {
		if (Salle[CurrentRoom].Get_Event() == Room::Event::Combat) {
			Game->PushState<Fight>(Game, window, player);
		}
	}

	if (CurrentRoom == Salle.size()) {
		for (auto* Current : player->Get_Squad()) {
			Current->Reset();
		}
		Game->PopState();
	}
}

void Dungeon::Display()
{
	for (Mercenary* Current : player->Get_Squad()) {
		if (Current->tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
			Current->Display(window, sf::Color::Magenta, font);
			Current->Display_Stat(window, font, sf::Vector2f(Current->Get_Position().x, Current->Get_Position().y + 185));
		}
		else
			Current->Display(window, sf::Color::Yellow, font);
	}
	if (CurrentRoom > 0)
		Back.Display(window);
	if (CurrentRoom < Salle.size())
		Next.Display(window);

	sf::Text tmp = CreateText("Room : " + std::to_string(CurrentRoom + 1) +
		"/" + std::to_string(Salle.size()), font, 50);
	tmp.setPosition(960, 50);
	window->draw(tmp);
}
