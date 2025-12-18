#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include "Global.h"

//List of all entities in the game
std::vector<Entity*> entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

std::unordered_map<std::string, sf::SoundBuffer> Game::soundBuffers;

size_t Game::score{}; //Game score

//Creates temporal asteroid spawn timer (AST)
//Unlike the other variable "asteroidSpawnTime", this one changes during gameplay
float Game::AST = 0.0f;

bool Game::isGameOver{};

//Define text and font
sf::Text Game::gameOverText{};
sf::Text Game::continueText{};
sf::Text Game::scoreText{};
sf::Font Game::font{};


//Initialization function that only runs once
//This way we don't call these other events inside that would normally be in begin()
void Game::init()
{
	//Set font of score text to Roboto (Can be changed to any font, just add to font folder)
	font.loadFromFile("fonts/Roboto-ExtraBold.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(30, 20));
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);

	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(350, 350));
	gameOverText.setCharacterSize(96);
	gameOverText.setString("Game Over!");

	continueText.setFont(font);
	continueText.setPosition(sf::Vector2f(450, 550));
	continueText.setCharacterSize(24);
	continueText.setString("Press SPACE to try again!");

	soundBuffers["shoot"].loadFromFile("audio/shoot.wav");
}

//Game begin event
void Game::begin()
{
	isGameOver = false;
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

	if (isGameOver)
	{
		entities.clear();
		score = 0;
		window.draw(gameOverText);
		window.draw(continueText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			begin();
		}

	}
}

void Game::gameOver()
{
	isGameOver = true;
}
