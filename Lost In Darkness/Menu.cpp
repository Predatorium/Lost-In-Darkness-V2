#include "Menu.h"
#include "State_Manager.h"
#include "Ressource_Manager.h"
#include "Headquarter.h"
#include "Tools.h"

Menu::Menu(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	Bouton.clear();
	Selection = 0;
	timer = 0;
	font = Ressource_Manager::AddAnyRessources<sf::Font>("MetalMacabre");
	sprite.setTexture(Ressource_Manager::AddAnyRessources<sf::Texture>("Main_Menu"));

	Title = Button(CreateText("Lost In Darkness", font, 150), CreateRectangle(), sf::Vector2f(960, 120), [] {});

	Bouton.push_back(Button(CreateText("New Game", font, 70), CreateRectangle(), sf::Vector2f(480, 530), 
		[this] {Game->PushState<Headquarter>(Game, window); }));

	Bouton.push_back(Button(CreateText("Load Game", font, 70), CreateRectangle(), sf::Vector2f(480, 658),
		[this] {Game->ChangeState<Menu>(Game, window); }));

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

		break;
	default:
		break;
	}
}

void Menu::Update(const float& dt)
{
	std::for_each(std::begin(Bouton), std::end(Bouton), [](Button& b) {b.Update(); });
}

void Menu::Display()
{
	window->draw(sprite);

	std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });

	Title.Display(window);	
}

