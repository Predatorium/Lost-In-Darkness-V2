#pragma once
#include <stack>
#include "SFML/Graphics.hpp"
#include <thread>
#include <mutex>

class State;

class State_Manager
{
public:
	State_Manager() = default;
	State_Manager(sf::RenderWindow* _window);
	~State_Manager();

	template<typename T, class ...Args>
	void ChangeState(Args ...args);

	template<typename T, class ...Args>
	void PushState(Args ...args);

	void PopState();

	void HandleEvents(sf::Event e);
	void Update(const float& dt);
	void Display();

private:
	std::stack<State*> states;
	sf::RenderWindow* window;

	sf::CircleShape Shape[5];

	std::thread threading;
	std::mutex m;
	std::unique_lock<std::mutex> Check_Mutex = std::unique_lock<std::mutex>(m, std::defer_lock);
};

template<typename T, class ...Args>
inline void State_Manager::ChangeState(Args ...args)
{
	while (!states.empty())
		states.pop();

	if (threading.joinable())
		threading.join();

	threading = std::thread([&]
		{
			Check_Mutex.lock();
			states.push(new T(args...));
			Check_Mutex.unlock();
		});
}

template<typename T, class ...Args>
inline void State_Manager::PushState(Args ...args)
{
	if (!states.empty())
		states.top()->Pause();

	if (threading.joinable())
		threading.join();

	threading = std::thread([&]
		{
			Check_Mutex.lock();
			states.push(new T(args...));
			Check_Mutex.unlock();
		});
}
