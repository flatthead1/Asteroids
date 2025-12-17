#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(sf::Vector2f position, float angle)
		: position(position), angle(angle){}

	//Both are virtual so they can be overridden
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	//Established position and angle for all entities
	sf::Vector2f position;
	float angle;
};