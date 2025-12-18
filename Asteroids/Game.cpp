#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include "Global.h"
#include <fstream>

//List of all entities in the game
std::vector<Entity*> entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

std::unordered_map<std::string, sf::SoundBuffer> Game::soundBuffers;

size_t Game::score{}; //Game score
size_t Game::highScore{}; //Highscore

//Creates temporal asteroid spawn timer (AST)
//Unlike the other variable "asteroidSpawnTime", this one changes during gameplay
float Game::AST = 0.0f;

Game::State Game::state{};

//Define text and font
sf::Font Game::font{};
sf::Text Game::scoreText{};

sf::Text Game::gameOverText{};
sf::Text Game::continueText{};

sf::Text Game::highScoreText{};
sf::Text Game::titleText{};
sf::Text Game::menuText{};
sf::Text Game::quitText{};
sf::Text Game::playText{};


//Initialization function that only runs once
//This way we don't call these other events inside that would normally be in begin()
void Game::init()
{
	//Get highscore file (std::ios::in for input) initialize first
	std::ifstream file("score.dat", std::ios::binary | std::ios::in);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
		file.close();
	}

	//Set font of score text to Roboto (Can be changed to any font, just add to font folder)
	font.loadFromFile("fonts/Roboto-ExtraBold.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(30, 20));
	scoreText.setCharacterSize(40);

	//Gameover text UI
	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(350, 350));
	gameOverText.setCharacterSize(96);
	gameOverText.setString("Game Over!");

	continueText.setFont(font);
	continueText.setPosition(sf::Vector2f(450, 550));
	continueText.setCharacterSize(24);
	continueText.setString("Press SPACE to try again!");

	highScoreText.setFont(font);
	highScoreText.setPosition(sf::Vector2f(40, 20));
	highScoreText.setCharacterSize(40);
	highScoreText.setString("High Score: " + std::to_string(highScore));

	//Main menu text UI
	titleText.setFont(font);
	titleText.setPosition(sf::Vector2f(350, 350));
	titleText.setCharacterSize(96);
	titleText.setString("ASTEROIDS");

	menuText.setFont(font);
	menuText.setPosition(sf::Vector2f(440, 600));
	menuText.setCharacterSize(24);
	menuText.setString("Press BACK to exit to menu");

	quitText.setFont(font);
	quitText.setPosition(sf::Vector2f(470, 650));
	quitText.setCharacterSize(24);
	quitText.setString("Press ESC to exit game");

	playText.setFont(font);
	playText.setPosition(sf::Vector2f(480, 550));
	playText.setCharacterSize(24);
	playText.setString("Press ENTER to play!");

	soundBuffers["shoot"].loadFromFile("audio/shoot.wav");

	state = MENU; //Set gamestate to MENU on initialization


}

//Game begin event
void Game::begin()
{
	state = PLAYING; //Change gamestate
	entities.push_back(new Player()); //Create player
	float AST = asteroidSpawnTime; //Reset AST to original spawn time value
	//If score is higher than stored highScore, change highscore file to that score
	

	score = 0;
}

//Game update event
void Game::update(sf::RenderWindow& window, float deltaTime)
{
	//Main Menu state
	if (state == MENU)
	{
		window.draw(highScoreText);
		window.draw(titleText);
		window.draw(playText);
		window.draw(quitText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Begin game if ENTER is pressed
		{
			begin();
		}
		return;
	}

	//Clears the lists at the start of every frame
	toAddList.clear();
	toRemoveList.clear();

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
	
	//State of game where you're actually playing the game
	//This only exists so the score only display during the game itself
	if (state == PLAYING)
	{
		//Set score to a string and draw to screen
		scoreText.setString(std::to_string(score));
		window.draw(scoreText);
	}

	//Game Over state
	if (state == GAME_OVER)
	{
		entities.clear(); //clear any entities on screen
		score = 0;

		//Show game over text + options
		window.draw(gameOverText);
		window.draw(continueText);
		window.draw(menuText);
		window.draw(quitText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //Restart game (SPACE)
		{
			begin();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) //Go to menu (BACKSPACE)
		{
			state = MENU;
		}

	}
}

//Game Over function
void Game::gameOver()
{
	//If score is higher than stored highscore, then change highscore or score.dat to current score
	if (score > highScore)
	{
		highScore = score;
		std::ofstream file("score.dat", std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
			file.close();
		}
		else //if failed to open file
		{
			printf("Failed to write high score to file\n");
		}

		//Change high score text
		highScoreText.setString("High Score: " + std::to_string(highScore));
	}

	state = GAME_OVER;
}
