#pragma once

class Room
{
public :
	enum class Event { Rien, Combat, Soin };
	Room() = default;
	Room(Event _event) : eEvent{ _event } {};
	~Room() = default;

	inline Event Get_Event() { return eEvent; }
	inline void Win() { eEvent = Event::Rien; }

private:
	Event eEvent;

};

