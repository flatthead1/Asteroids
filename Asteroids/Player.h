#pragma once
#include "Asteroid.h"
#include "Entity.h"
#include <SFML/Audio.hpp>

//Player variables
constexpr float playerWidth = 50.0f;
constexpr float playerHeight = 40.0f;
constexpr float turnSpeed = 200.0f;

class Player : public Entity {
public:
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

	//Runtime tuning for movement acceleration
	void setMaxSpeed(float s) { maxSpeed = s; }
	void setAcceleration(float a) { acceleration = a; }
	void setDeceleration(float d) { deceleration = d; }
	float getSpeed() const { return playerSpeed; }

private:
	sf::VertexArray array;
	sf::Sound shootSound;

	float shootTimer;

	//Movement state and tuning
	float playerSpeed = 0.0f;
	float maxSpeed = 300.0f;
	float acceleration = 400.0f;
	float deceleration = 300.0f;
};