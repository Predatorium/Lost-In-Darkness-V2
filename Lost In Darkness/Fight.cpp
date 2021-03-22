#include "Fight.h"
#include "State_Manager.h"
#include "Ressource_Manager.h"
#include "Menu.h"
#include "Tools.h"

Fight::Fight(State_Manager* game, sf::RenderWindow* _window) : State(game, _window)
{
	std::list<Mercenary> tmp;
	tmp.push_back(Me_Box.Get_Box(Mercenary::Type::Assasin));
	tmp.push_back(Me_Box.Get_Box(Mercenary::Type::Chevalier));
	tmp.push_back(Me_Box.Get_Box(Mercenary::Type::Pretre));
	tmp.push_back(Me_Box.Get_Box(Mercenary::Type::Sorcier));
	player = Player(tmp);

	Enemy.push_back(Mo_Box.Get_Box(Monster::Type::Ghoul));
	Enemy.push_back(Mo_Box.Get_Box(Monster::Type::Ghoul));
	Enemy.push_back(Mo_Box.Get_Box(Monster::Type::Ghoul));
	Enemy.push_back(Mo_Box.Get_Box(Monster::Type::Ghoul));

	font = Ressource_Manager::AddAnyRessources<sf::Font>("Vamp");
	sprite.setTexture(Ressource_Manager::AddAnyRessources<sf::Texture>("Fight"));

	Bouton.push_back(Button(CreateText("Skill : 1", font, 30), 2, { 240 , 850 },
		sf::Color::White, sf::Color::Transparent, [this] {Skill_Select = 0; return 0; }));
	Bouton.push_back(Button(CreateText("Skill : 2", font, 30), 2, { Bouton.back().Get_Shape().getPosition().x + 120,
		Bouton.back().Get_Shape().getPosition().y }, sf::Color::White, sf::Color::Transparent, [this] {Skill_Select = 1; return 0; }));

	int i = 1;
	for (Mercenary& Current : player.Get_Squad())
	{
		Current.Set_Position(960.f - (200.f * i), 665.f);
		i++;
	}

	i = 1;
	for (Monster& Current : Enemy)
	{
		Current.Set_Position(960.f + (200.f * i), 665.f);
		i++;
	}

	etape = Etape::Attack;
	turn = (float)Enemy.size() + (float)player.Get_Squad().size() + 1.f;
	timer = 0.f;
	Enemy_Selection = 0;
	Skill_Select = -1;
	EffectUpdate = false;
}

void Fight::Turn_Order()
{
	for (Mercenary& Current : player.Get_Squad())
		Current.Res_TurnOrder();

	for (Monster& Current : Enemy)
		Current.Res_TurnOrder();

	for (Mercenary& Current : player.Get_Squad())
		for (Mercenary& Current2 : player.Get_Squad())
			if (Current != Current2)
				if (Current.Get_Speed() <= Current2.Get_Speed())
				{
					if (Current.Get_Speed() == Current2.Get_Speed() && Current.Get_TurnOrder() == Current2.Get_TurnOrder())
						Current2.Add_TurnOrder();
					else if (Current.Get_Speed() < Current2.Get_Speed())
						Current.Add_TurnOrder();
				}

	for (Monster& Current : Enemy)
		for (Monster& Current2 : Enemy)
			if (Current != Current2)
				if (Current.Get_Speed() <= Current2.Get_Speed())
				{
					if (Current.Get_Speed() == Current2.Get_Speed() && Current.Get_TurnOrder() == Current2.Get_TurnOrder())
						Current2.Add_TurnOrder();
					else if (Current.Get_Speed() < Current2.Get_Speed())
						Current.Add_TurnOrder();
				}

	for (Monster& Current : Enemy)
		for (Mercenary& Current2 : player.Get_Squad())
		{
			if (Current.Get_Speed() <= Current2.Get_Speed())
				Current.Add_TurnOrder();
			if (Current.Get_Speed() > Current2.Get_Speed())
				Current2.Add_TurnOrder();
		}
}

void Fight::HandleEvents(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Key::Escape)
			Game->PopState();

		break;
	default:
		break;
	}

	if (Enemy.size() == 0)
		Game->PopState();
	if (player.Get_Squad().size() == 0)
		Game->PopState();
}

void Fight::Update(const float& dt)
{
	if (turn > Enemy.size() + player.Get_Squad().size())
	{
		Turn_Order();
		turn = 1;
	}

	for (Mercenary& Current : player.Get_Squad())
		if (Current.Get_TurnOrder() == turn) {
			if (EffectUpdate == false) {
				Current.Effect_Update();
				EffectUpdate = true;

				if (Current.Get_Life() == 0) {
					player.Get_Squad().remove_if([](Mercenary& m) {return m.Get_Life() == 0; });
					Turn_Order();
					break;
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (Skill_Select != -1)	{
					if (Current.Get_Skill(Skill_Select).Get_Type() == Skill::Type::Ennemy)
						for (Monster& Current2 : Enemy)
							if (Current2.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
								Current.Attack(Current2, Skill_Select);
								turn++;

								Skill_Select = -1;
								EffectUpdate = false;

								Enemy.remove_if([](Monster& m) {return m.Get_Life() == 0; });
								Turn_Order();
								break;
							}

					if (Current.Get_Skill(Skill_Select).Get_Type() == Skill::Type::Ally)
						for (Mercenary& Current2 : player.Get_Squad())
							if (Current2.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
								Current.Buff(Current2, Skill_Select);
								turn++;

								Skill_Select = -1;
								EffectUpdate = false;
								break;
							}
				}

				int i = 0;
				for (Button& Current2 : Bouton)	{
					Current2.Set_Text(Current.Get_Skill(i).Get_Name());
					if (Current2.Get_Shape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
						Skill_Select = Current2.Update();
						break;
					}
					i++;
				}
			}

			int i = 0;
			for (Button& Current2 : Bouton)	{
				Current2.Set_Text(Current.Get_Skill(i).Get_Name());
				Current2.Set_Position(sf::Vector2f(360 + i * 200,850));
				i++;
			}

			break;
		}

	for (Monster& Current : Enemy)
		if (Current.Get_TurnOrder() == turn){
			if (EffectUpdate == false){
				Current.Effect_Update();
				EffectUpdate = true;

				if (Current.Get_Life() == 0)
				{
					Enemy.remove_if([](Monster& m) {return m.Get_Life() == 0; });
					Turn_Order();
					break;
				}
			}

			timer += dt;

			if (Enemy_Selection == 0)
				Enemy_Selection = irandom(1, player.Get_Squad().size());

			if (timer > 1.5f){
				int x = player.Get_Squad().size();
				for (Mercenary& Current2 : player.Get_Squad()){
					if (x == Enemy_Selection){
						Current.Attack(Current2, 0);
						turn++;
						timer = 0;
						Enemy_Selection = 0;
						EffectUpdate = false;
						player.Get_Squad().remove_if([](Mercenary& m) {return m.Get_Life() == 0; });
						Turn_Order();
						break;
					}
					x--;
				}
			}
			break;
		}
}

void Fight::Display()
{
	window->draw(sprite);

	int i = Enemy.size();
	for (Monster& Current : Enemy)
	{
		if (Current.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
		{
			Current.Display(window, sf::Color::Magenta, font);
			Current.Display_Stat(window, font, { 1680, 850 });
		}
		else if (Current.Get_TurnOrder() == turn)
		{
			Current.Display(window, sf::Color::Cyan, font);
			Current.Display_Stat(window, font, { 1680, 850 });
		}
		else
			Current.Display(window, sf::Color::Red, font);
		
		i--;
	}

	i = player.Get_Squad().size();
	for (Mercenary& Current : player.Get_Squad())
	{
		if (i == Enemy_Selection || Current.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
		{
			Current.Display(window, sf::Color::Magenta, font);
			if (i == Enemy_Selection)
				Current.Display_Stat(window, font, { 120, 850 });
			else
				Current.Display_Stat(window, font, { 780, 850 });
		}
		else
			Current.Display(window, sf::Color::Blue, font);
		if (Current.Get_TurnOrder() == turn)
		{
			Current.Display(window, sf::Color::Yellow, font);
			Current.Display_Stat(window, font, { 120, 850 });
			if (Skill_Select >= 0)
				Current.Get_Skill(Skill_Select).Display(window, font, { 420, 885 });
		}

		i--;
	}

	for (auto current : Bouton)
		current.Display(window);
}