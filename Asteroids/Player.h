#pragma once
#include "Asteroid.h"
#include "Entity.h"

constexpr float playerWidth = 50.0f;
constexpr float playerHeight = 40.0f;
constexpr float turnSpeed = 200.0f;
constexpr float playerSpeed = 200.0f;

class Player : public Entity {
public:
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::VertexArray array;

	float shootTimer;
};