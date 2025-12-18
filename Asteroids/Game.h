#pragma once

#include <unordered_map>
#include <vector>
#include <list>
#include "Entity.h"
#include <SFML/Audio.hpp>

class Game
{
public:
	static void init();
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static void gameOver();

	//Making a list to remove bullets so they don't exist infinitely
	//Don't want to delete then while they are being used in the main loop, causes problems
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static size_t score;

	static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

private:
	static float AST;
	static sf::Text scoreText;
	static sf::Text gameOverText;
	static sf::Text continueText;
	static sf::Font font;

	static bool isGameOver;
};

