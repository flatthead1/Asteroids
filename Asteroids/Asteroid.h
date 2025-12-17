#pragma once
#include "Entity.h"
#include "Global.h"

constexpr float asteroidWidth = 90.0f;
constexpr float asteroidHeight = 80.0f;
constexpr float asteroidSpin = 25.0f;
constexpr float asteroidSpeed = 200.0f;
constexpr float asteroidSpawnTime = 3.0f;

class Asteroid : public Entity
{
public:
	Asteroid(const sf::Vector2f& direction = Asteroid::getRandomDirection(),
		sf::Vector2f position = Asteroid::getRandomPosition());

	void update(float deltaTime) override;
	

	//References RenderWindow called "window" (RenderWindow&)
	void render(sf::RenderWindow& window) override;

	//Randomizes direction for asteroid movement
	static sf::Vector2f getRandomDirection();

	//Randomizes position for asteroid spawn (identical code as getRandomDirection())
	static sf::Vector2f getRandomPosition();

private:
	sf::VertexArray array;
	sf::Vector2f direction;
};

