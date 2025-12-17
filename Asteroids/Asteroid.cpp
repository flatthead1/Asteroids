#include "Asteroid.h"
#include "Global.h"
#include <random>

Asteroid::Asteroid(const sf::Vector2f& direction, sf::Vector2f position)
	: Entity(sf::Vector2f(900, 300), 0), direction(direction), array(sf::LinesStrip, 12)
	{
		//Making the asteroid shape
		array[0].position = sf::Vector2f(-40, 40);
		array[1].position = sf::Vector2f(-50, 10);
		array[2].position = sf::Vector2f(-10, -20);
		array[3].position = sf::Vector2f(-20, -40);
		array[4].position = sf::Vector2f(10, -40);
		array[5].position = sf::Vector2f(40, -20);
		array[6].position = sf::Vector2f(40, -10);
		array[7].position = sf::Vector2f(20, 0);
		array[8].position = sf::Vector2f(40, 20);
		array[9].position = sf::Vector2f(20, 40);
		array[10].position = sf::Vector2f(0, 30);
		array[11].position = array[0].position; //Close shape

		//Setting each of the vertices to white
		for (size_t i = 0; i < array.getVertexCount(); i++)
		{
			array[i].color = sf::Color::White;
		}
	}

void Asteroid::update(float deltaTime)
{
	//Asteroid movement
	position += asteroidSpeed * direction * deltaTime;
	angle += asteroidSpin * deltaTime;

	//Bounce off edges of screen
	if (position.x < asteroidWidth / 2.0f)
	{
		direction.x = abs(direction.x);
	}
	else if (position.x > screenWidth - asteroidWidth / 2.0f)
	{
		direction.x = -abs(direction.x);
	}

	if (position.y < asteroidHeight / 2.0f)
	{
		direction.y = abs(direction.y);
	}
	else if (position.y > screenHeight - asteroidHeight / 2.0f)
	{
		direction.y = -abs(direction.y);
	}
}

//Draw asteroid to screen
void Asteroid::render(sf::RenderWindow& window)
{
	window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& Asteroid::getVertexArray() const
{
	return array;
}

sf::Vector2f Asteroid::getRandomDirection()
{
	//Get random angle in radians
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

	//Convert angle to direction vector
	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}

sf::Vector2f Asteroid::getRandomPosition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xAxis(asteroidWidth / 2.0f,
		screenWidth - asteroidWidth / 2.0f);
	std::uniform_real_distribution<float> yAxis(asteroidHeight / 2.0f,
		screenHeight - asteroidHeight / 2.0f);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}