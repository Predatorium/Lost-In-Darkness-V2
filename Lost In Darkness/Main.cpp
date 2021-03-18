#include "Game_Manager.h"
#include <thread>

int main()
{
	Game_Manager Main(sf::VideoMode(1920,1080), "Lost In Darkness", sf::Style::Fullscreen);

	Main.GameLoop();

	return 0;
}