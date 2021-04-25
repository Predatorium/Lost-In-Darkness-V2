#include "Menu.h"
#include "State_Manager.h"
#include "Ressource_Manager.h"
#include "Headquarter.h"
#include "Tools.h"

Menu::Menu(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	Bouton.clear();
	font = Ressource_Manager::AddAnyRessources<sf::Font>("MetalMacabre");
	sprite.setTexture(Ressource_Manager::AddAnyRessources<sf::Texture>("Main_Menu"));

	Title = CreateText("Lost In Darkness", font, 150);
	Title.setPosition(960, 120);

	Bouton.push_back(Button(CreateText("New Game", font, 70), CreateRectangle(), sf::Vector2f(480, 530),
		[this] {Game->PushState<Headquarter>(Game, window); }));

	Bouton.push_back(Button(CreateText("Option", font, 70), CreateRectangle(), sf::Vector2f(480, 771),
		[this] {Game->ChangeState<Menu>(Game, window); }));

	Bouton.push_back(Button(CreateText("Quit", font, 70), CreateRectangle(), sf::Vector2f(480, 876),
		[this] {Game->PopState(); }));
}

void Menu::HandleEvents(sf::Event e)
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

void Menu::Update(const float& dt)
{
	for (auto it = std::begin(Bouton); it != std::end(Bouton); it++) {
		if (it->Update()) {
			break;
		}
	}
}

void Menu::Display()
{
	window->draw(sprite);

	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });

	window->draw(Title);
}