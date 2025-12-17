#include "Bullet.h"
#include "Entity.h"
#include "Global.h"

void Bullet::update(float deltaTime)
{
	lifetime -= deltaTime;

	position += direction * bulletSpeed * deltaTime;

	//If lifetime is 0 or less, remove bullet
	if (lifetime <= 0.0f)
	{
		Game::toRemoveList.push_back(std::find(entities.begin(), entities.end(), this));
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}