#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include "Global.h"


std::vector<Entity*> entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

float Game::AST = 0.0f;

void Game::begin()
{
	entities.push_back(new Player());

	float AST = asteroidSpawnTime;

}

void Game::update(sf::RenderWindow& window, float deltaTime)
{

	//Clears the lists at the start of every frame
	toAddList.clear();
	toRemoveList.clear();

	//Clears window to black (default)
	window.clear();

	AST -= deltaTime;

	//Rendering entities
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->update(deltaTime);
		entities[i]->render(window);
	}

	//Lists for bullets during the frame
	for (const auto& it : Game::toRemoveList)
	{
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : Game::toAddList)
	{
		entities.push_back(ptr);
	}

	//Spawning asteroids
	if (AST <= 0.0f)
	{
		entities.push_back(new Asteroid());
		AST = asteroidSpawnTime;
	}

}