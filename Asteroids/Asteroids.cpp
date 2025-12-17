#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include <list>
#include <random>
#include "Global.h"
#include "Entity.h"
#include "Player.h"
#include "Asteroid.h"
#include "Game.h"

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	//RenderWindow used so window.clear() works, draws into window
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids", sf::Style::Close | sf::Style::Titlebar); //Makes window unresizable
	sf::Clock clock;

	Game::begin();

	//Centers player by window size
	sf::Vector2u ws = window.getSize();
	sf::Vector2f center(static_cast<float>(ws.x) / 2.0f, static_cast<float>(ws.y) / 2.0f);
	
	entities.push_back(new Asteroid(Asteroid::getRandomDirection())); //Creates new asteroid w/ random direction

	float AST = asteroidSpawnTime; //Temporary variable to reset spawn time

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

		Game::update(window, deltaTime);

		//Draws game
		window.display();

	}
}
