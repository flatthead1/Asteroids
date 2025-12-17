#include "Bullet.h"
#include "Entity.h"
#include "Global.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Game.h"

//Update bullet position and check for collisions
void Bullet::update(float deltaTime)
{
	lifetime -= deltaTime; //Decreasing lifetime as game goes on

	position += direction * bulletSpeed * deltaTime; //Moves bullet

	//If lifetime is 0 or less, remove bullet
	if (lifetime <= 0.0f)
	{
		Game::toRemoveList.push_back(std::find(entities.begin(), entities.end(), this));
	}

	//Check for collision with asteroids
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (typeid(*entities[i]) == typeid(Asteroid)) 
		{
			Asteroid* asteroid = dynamic_cast<Asteroid*>(entities[i]); //Create asteroid pointer to current entity
			sf::Transform transform = sf::Transform()
				.translate(asteroid->position)
				.rotate(asteroid->angle);

			//Check for intersection between bullet and asteroid polygon
			if (collision::intersects(position, collision::getTransformed(asteroid->getVertexArray(), transform)))
			{
				lifetime = 0.0f; //Set lifetime to 0 to remove bullet
				Game::toRemoveList.push_back(std::find(entities.begin(), entities.end(), asteroid)); //Remove asteroid
				Game::score += 10; //Increase score
			}
		}
	}
}

//Draw bullet to screen
void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}