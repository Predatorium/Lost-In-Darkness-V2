#include "Fight.h"
#include "State_Manager.h"
#include "Ressource_Manager.h"
#include "Menu.h"
#include "Tools.h"

Fight::Fight(State_Manager* game, sf::RenderWindow* _window, Player* joueur, int Difficulté)
	: State(game, _window), player(joueur)
{
	if (Difficulté == 1) {
		int i = irandom(2, 4);
		for (int x = 0; x < i; x++)
			Enemy.push_back(Mo_Box.Rand_BoxEasy());
	}
	if (Difficulté == 2) {
		int i = irandom(3, 4);
		for (int x = 0; x < i; x++)
			Enemy.push_back(Mo_Box.Rand_BoxNormal());
	}
	if (Difficulté == 3) {
		for (int x = 0; x < 4; x++)
			Enemy.push_back(Mo_Box.Rand_BoxHard());
	}

	font = Ressource_Manager::AddAnyRessources<sf::Font>("Vamp");
	
	Action.setCharacterSize(50);
	Action.setFont(font);
	Action.setPosition(960, 450);

	Bouton.push_back(Button(CreateText("Skill : 1", font, 30), CreateRectangle(2.f),
		{ 240 , 850 }, [this] {Skill_Select = 0; }));
	Bouton.push_back(Button(CreateText("Skill : 2", font, 30), CreateRectangle(2.f),
		{ Bouton.back().Get_Shape().getPosition().x + 120,
		Bouton.back().Get_Shape().getPosition().y }, [this] {Skill_Select = 1; }));

	Turn_Order();
}

void Fight::Turn_Order()
{
	std::for_each(std::begin(player->Get_Squad()), std::end(player->Get_Squad()),
		[](Mercenary* m) {m->Turn_Order = 1; });
	std::for_each(std::begin(Enemy), std::end(Enemy),
		[](Monster& m) {m.Turn_Order = 1; });

	int i = 1;
	for (auto Current : player->Get_Squad()) {
		Current->Set_Position(960.f - (200.f * i), 665.f);
		i++;
	}

	i = 1;
	for (Monster& Current : Enemy) {
		Current.Set_Position(960.f + (200.f * i), 665.f);
		i++;
	}

	for (Mercenary* Current : player->Get_Squad()) {
		for (Mercenary* Current2 : player->Get_Squad()) {
			if (Current != Current2) {
				if (Current->Speed > Current2->Speed) {
					Current2->Turn_Order++;
				}
				if (Current->Speed == Current2->Speed &&
					Current->Turn_Order == Current2->Turn_Order) {
					Current2->Turn_Order++;
				}
			}
		}
	}

	for (Monster& Current : Enemy) {
		for (Monster& Current2 : Enemy) {
			if (Current != Current2) {
				if (Current.Speed > Current2.Speed) {
					Current2.Turn_Order++;
				}
				if (Current.Speed == Current2.Speed &&
					Current.Turn_Order == Current2.Turn_Order) {
					Current2.Turn_Order++;
				}
			}
		}
	}

	for (Monster& Current : Enemy) {
		for (Mercenary* Current2 : player->Get_Squad()) {
			if (Current.Speed <= Current2->Speed)
				Current.Turn_Order++;
			if (Current.Speed > Current2->Speed)
				Current2->Turn_Order++;
		}
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

void Fight::Update(const float& dt)
{
	if (turn > Enemy.size() + player->Get_Squad().size()) {
		Turn_Order();
		turn = 1;
	}

	if (etape != Etape::Affiche) {
		for (Mercenary* Current : player->Get_Squad()) {
			if (Current->Turn_Order == turn && etape != Etape::Affiche) {
				if (EffectUpdate == false) {
					etape = Etape::Me;
					text = Current->Get_Name();
					text3 = "C'est au tour de " + Current->Get_Name();
					Selected = false;
					Current->Effect_Update();
					EffectUpdate = true;

					if (Current->Get_Life() == 0) {
						player->Get_Squad().remove_if([](Mercenary* m) {return m->Get_Life() == 0; });
						Turn_Order();
						break;
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (Skill_Select != -1) {
						if (Current->Get_Skill(Skill_Select).Get_Type() == Skill::Type::Ennemy)
							for (Monster& Current2 : Enemy)
								if (Current2.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
									Damage = Current->Attack(Current2, Skill_Select);
									text = Current2.Get_Name() + " a recu " + std::to_string(Damage) + " de degat.";
									text2 = "";
									turn++;
									etape = Etape::Affiche;
									Skill_Select = -1;
									EffectUpdate = false;

									Enemy.remove_if([](Monster& m) {return m.Get_Life() == 0; });
									Turn_Order();
									break;
								}

						if (Current->Get_Skill(Skill_Select).Get_Type() == Skill::Type::Ally)
							for (Mercenary* Current2 : player->Get_Squad())
								if (Current2->tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
									Current->Buff(*Current2, Skill_Select);
									turn++;

									text = Current2->Get_Name() + " a recu " + Current->Get_Skill(Skill_Select).Get_Name();
									text2 = "";

									Skill_Select = -1;
									etape = Etape::Affiche;
									EffectUpdate = false;
									break;
								}
					}
				}

				int i = 0;
				std::for_each(std::begin(Bouton), std::end(Bouton), [&i, &Current](Button& b) {
					b.Set_Text(Current->Get_Skill(i).Get_Name());
					b.Set_Position(sf::Vector2f(360 + i * 200, 850));
					b.Update();
					i++;
					});

				break;
			}
		}
	}

	if (etape != Etape::Affiche) {
		for (Monster& Current : Enemy) {
			if (Current.Turn_Order == turn) {
				Selected = true;
				if (EffectUpdate == false) {
					etape = Etape::Enemy;
					text = Current.Get_Name();
					EffectUpdate = true;
					Current.Effect_Update();

					if (Current.Get_Life() == 0) {
						Enemy.remove_if([](Monster& m) {return m.Get_Life() == 0; });
						Turn_Order();
						break;
					}
				}

				timer += dt;

				if (Enemy_Selection == 0) {
					Enemy_Selection = irandom(1, player->Get_Squad().size());
					int x = player->Get_Squad().size();
					for (Mercenary* Current2 : player->Get_Squad()) {
						if (x == Enemy_Selection) {
							text2 = " attaque " + Current2->Get_Name();
							break;
						}
						x--;
					}
				}

				if (timer > 2.5f){
					int x = player->Get_Squad().size();
					for (Mercenary* Current2 : player->Get_Squad()) {
						if (x == Enemy_Selection) {
							Damage = Current.Attack(*Current2, 0);
							text = Current2->Get_Name() + " a recu " + std::to_string(Damage) + " de degat.";
							text2 = "";
							etape = Etape::Affiche;
							turn++;
							timer = 0;
							Enemy_Selection = 0;
							EffectUpdate = false;
							player->Get_Squad().remove_if([](Mercenary* m) {return m->Get_Life() == 0; });
							Turn_Order();
							break;
						}
						x--;
					}
				}
				break;
			}
		}
	}

	if (etape == Etape::Affiche) {
		timer += dt;
		if (timer > 2.5f) {
			timer = 0;
			etape = Etape::Me;
		}
	}

	if (!Selected) {
		Action.setString(text3);
	}
	else {
		Action.setString(text + text2);
	}

	Action.setOrigin(getMidle(Action));

	if (Enemy.size() == 0) {
		player->ResetEffect();
		Game->PopState();
	}
	if (player->Get_Squad().size() == 0)
		Game->PopState();
}

void Fight::Display()
{
	for (Monster& Current : Enemy) {
		if (Current.tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
			Current.Display(window, sf::Color::Magenta, font);
			Current.Display_Stat(window, font, { 1650, 850 });
			if (etape == Etape::Me) {
				Selected = true;
				text2 = " attaque " + Current.Get_Name();
			}
		}
		else if (Current.Turn_Order == turn) {
			Current.Display(window, sf::Color::Cyan, font);
			Current.Display_Stat(window, font, { 1800, 850 });
		}
		else
			Current.Display(window, sf::Color::Red, font);
	}

	int i = player->Get_Squad().size();
	for (Mercenary* Current : player->Get_Squad()) {
		if (i == Enemy_Selection || Current->tmp.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
			Current->Display(window, sf::Color::Magenta, font);
			if (i == Enemy_Selection)
				Current->Display_Stat(window, font, { 120, 850 });
			else {
				Current->Display_Stat(window, font, { 780, 850 });
				if (etape == Etape::Me) {
					Selected = true;
					text2 = " aide " + Current->Get_Name();
				}
			}
		}
		else
			Current->Display(window, sf::Color::Blue, font);

		if (Current->Turn_Order == turn) {
			Current->Display(window, sf::Color::Yellow, font);
			Current->Display_Stat(window, font, { 120, 850 });
			if (Skill_Select >= 0)
				Current->Get_Skill(Skill_Select).Display(window, font, { 420, 885 });
		}

		i--;
	}

	if (etape == Etape::Me) {
		std::for_each(std::begin(Bouton), std::end(Bouton), [this](Button& b) {b.Display(window); });
	}

	window->draw(Action);
}