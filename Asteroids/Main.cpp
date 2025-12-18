#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include "Physics.h"
#include "Game.h"

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	//RenderWindow used so window.clear() works, draws into window
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids", sf::Style::Close | sf::Style::Titlebar); //Makes window unresizable
	sf::Clock clock;

	Game::init();
	
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds(); //Restart the clock and gives it the time since last restart in seconds
		sf::Event e{};
		while (window.pollEvent(e))
		{
			//Lets you close the window by either pressing ESC or with the X button on the top right
			if (e.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

		}

		window.clear(); //Set game to black screen by default, should be first on priority

		Game::update(window, deltaTime); //Updates game by deltaTime

		//Draws game
		window.display();

	}
}
