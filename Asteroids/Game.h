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
	static size_t highScore;
	//Gameplay elements
	static sf::Font font;
	static sf::Text scoreText;
	//Gameover elements
	static sf::Text gameOverText;
	static sf::Text continueText;
	//Main Menu elements
	static sf::Text highScoreText;
	static sf::Text titleText;
	static sf::Text menuText;
	static sf::Text quitText;
	static sf::Text playText;


	//Define the different states the game can be in
	static enum State { MENU, PLAYING, GAME_OVER } state;
};

