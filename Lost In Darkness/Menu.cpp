#include "Menu.h"
#include "State_Manager.h"
#include "Ressource_Manager.h"
#include "Fight.h"
#include "Tools.h"

Menu::Menu(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	Bouton.clear();
	Selection = 0;
	timer = 0;
	font = Ressource_Manager::AddAnyRessources<sf::Font>("../Ressources/Fonts/MetalMacabre.ttf");
	sprite.setTexture(Ressource_Manager::AddAnyRessources<sf::Texture>("../Ressources/Main_Menu.jpg"));

	Title = Button(CreateText("Lost In Darkness", font, 150), 5.f, sf::Vector2f(960, 120), sf::Color::White,
		sf::Color::Transparent, [] {return 0; });

	Bouton.push_back(Button(CreateText("New Game", font, 70), 3, sf::Vector2f(480, 530), sf::Color::White,
		sf::Color::Transparent, [game, _window] {game->ChangeState<Fight>(game, _window); return 0; }));

	Bouton.push_back(Button(CreateText("Load Game", font, 70), 3, sf::Vector2f(480, 658), sf::Color::White,
		sf::Color::Transparent, [game, _window] {game->ChangeState<Menu>(game, _window); return 0; }));

	Bouton.push_back(Button(CreateText("Option", font, 70), 3, sf::Vector2f(480, 771), sf::Color::White,
		sf::Color::Transparent, [game, _window] {game->ChangeState<Menu>(game, _window); return 0; }));

	Bouton.push_back(Button(CreateText("Quit", font, 70), 3, sf::Vector2f(480, 876), sf::Color::White,
		sf::Color::Transparent, [game, _window] {game->PopState(); return 0; }));
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
	for (Button& Current : Bouton)
	{
		if (Current.Get_Shape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
			Current.Set_ColorText(sf::Color::Red);
		else
			Current.Set_ColorText(sf::Color::White);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		for (Button& Current : Bouton)
			if (Current.Get_Shape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
			{
				Current.Update();
			}

}

void Menu::Display()
{
	window->draw(sprite);

	for (Button& Current : Bouton)
		Current.Display(window);

	Title.Display(window);	
}

