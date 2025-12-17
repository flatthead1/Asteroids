#pragma once

#include <vector>
#include <list>
#include "Entity.h"

class Game
{
public:
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	//Making a list to remove bullets so they don't exist infinitely
	//Don't want to delete then while they are being used in the main loop, causes problems
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

private:
	static float AST;
};

