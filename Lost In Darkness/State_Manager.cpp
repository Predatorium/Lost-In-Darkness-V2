#include "State_Manager.h"
#include "State.h"

State_Manager::State_Manager(sf::RenderWindow* _window) : window{_window}
{
}

State_Manager::~State_Manager()
{
	while (!states.empty())
		states.pop();
}

void State_Manager::Init()
{
	for (int i = 0; i < 5; i++)
	{
		Shape[i].setRadius(i + 1 * 3);
		Shape[i].setOrigin({ 0,100 + Shape[i].getRadius() / 2});
		Shape[i].setPosition({ 960,540 });
		Shape[i].setRotation(i * 20);
	}
}

void State_Manager::ChangeState(State* state)
{
	while (!states.empty())
		states.pop();

	if (threading.joinable())
		threading.join();

	threading = std::thread([&]
		{
			Check_Mutex.lock();
			states.push(state);
			Check_Mutex.unlock();
		});
}

void State_Manager::PushState(State* state)
{
	if (!states.empty())
		states.top()->Pause();

	if (threading.joinable())
		threading.join();

	threading = std::thread([&]
		{
			Check_Mutex.lock();
			states.push(state);
			Check_Mutex.unlock();
		});
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
			states.top()->HandleEvents();
}

void State_Manager::Update()
{
	if (Check_Mutex)
	{
		for (int i = 0; i < 5; i++)
			Shape[i].rotate(150);
	}
	else if (!Check_Mutex)
	{
		if (!states.empty() && states.top())
			states.top()->Update();
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