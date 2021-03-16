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

	void Init();

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	void HandleEvents(sf::Event e);
	void Update();
	void Display();

private:
	std::stack<State*> states;
	sf::RenderWindow* window;

	sf::CircleShape Shape[5];

	std::thread threading;
	std::mutex m;
	std::unique_lock<std::mutex> Check_Mutex = std::unique_lock<std::mutex>(m, std::defer_lock);
};
