#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Global.h"
#include "Game.h"


//Bullet variables
constexpr float shootDelay = 0.5f;
constexpr float bulletSpeed = 400.0f;
constexpr float bulletLifetime = 3.0f;

class Bullet : public Entity
{
public:

	Bullet(sf::Vector2f position, sf::Vector2f direction)
		: shape(1.0f), direction(direction), Entity(position, 0.0f), lifetime(bulletLifetime) {
	}

	void update(float deltaTime) override;

	void render(sf::RenderWindow& window) override;


private:
	sf::Vector2f direction;
	sf::CircleShape shape;
	float lifetime;
};