#include "Bullet.h"
#include "Entity.h"
#include "Global.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Game.h"

void Bullet::update(float deltaTime)
{
	lifetime -= deltaTime;

	position += direction * bulletSpeed * deltaTime;

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

			if (collision::intersects(position, collision::getTransformedPolygon(asteroid->getVertexArray(), transform)))
			{
				lifetime = 0.0f; //Set lifetime to 0 to remove bullet
			}
		}
	}
}

//Draw bullet to screen
void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}