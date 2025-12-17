#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include "Global.h"

//List of all entities in the game
std::vector<Entity*> entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

size_t Game::score{}; //Game score

//Creates temporal asteroid spawn timer (AST)
//Unlike the other variable "asteroidSpawnTime", this one changes during gameplay
float Game::AST = 0.0f;

//Score text and font
sf::Text Game::scoreText{};
sf::Font Game::font{};

//Game begin event
void Game::begin()
{
	//Set font of score text to Roboto (Can be changed to any font, just add to font folder)
	font.loadFromFile("fonts/Roboto-ExtraBold.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(30, 20));
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);

	entities.push_back(new Player()); //Create player

	float AST = asteroidSpawnTime; //Reset AST to original spawn time value

}

//Game update event
void Game::update(sf::RenderWindow& window, float deltaTime)
{

	//Clears the lists at the start of every frame
	toAddList.clear();
	toRemoveList.clear();

	//Clears window to black (default)
	window.clear();

	AST -= deltaTime; //Decrease AST as game goes on

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

	//Set score to a string and draw to screen
	scoreText.setString(std::to_string(score));
	window.draw(scoreText);
}