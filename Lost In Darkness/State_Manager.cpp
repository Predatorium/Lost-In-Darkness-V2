#include "State_Manager.h"
#include "State.h"
#include "Menu.h"

State_Manager::State_Manager(sf::RenderWindow* _window) : window(_window)
{
	ChangeState<Menu>(this, window);

	for (int i = 0; i < 5; i++)
	{
		Shape[i].setRadius(i + 1 * 3);
		Shape[i].setOrigin({ 0,100 + Shape[i].getRadius() / 2 });
		Shape[i].setPosition({ 960,540 });
		Shape[i].setRotation(i * 20);
	}
}

State_Manager::~State_Manager()
{
	while (!states.empty())
		states.pop();
}

void State_Manager::PopState()
{
	if (!states.empty())
		states.pop();

	if (threading.joinable())
		threading.join();

	if (!states.empty())
		states.top()->Resume();
	else
		window->close();
}

void State_Manager::HandleEvents(sf::Event e)
{
	if (!Check_Mutex)
		if (!states.empty() && states.top())
			states.top()->HandleEvents(e);
}

void State_Manager::Update(const float& dt)
{
	if (Check_Mutex)
	{
		for (int i = 0; i < 5; i++)
			Shape[i].rotate(150);
	}
	else if (!Check_Mutex)
	{
		if (!states.empty() && states.top())
			states.top()->Update(dt);
	}
}

void State_Manager::Display()
{
	window->clear(sf::Color::Black);

	if (Check_Mutex)
	{
		for (int i = 0; i < 5; i++)
			window->draw(Shape[i]);
	}
	else
		if (!states.empty() && states.top())
			states.top()->Display();

	window->display();
}