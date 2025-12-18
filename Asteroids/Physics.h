#pragma once

#include <SFML/Graphics.hpp>

//Create collision events
namespace collision {
	bool intersects(const sf::Vector2f point, const sf::VertexArray& polygon);
	sf::VertexArray getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);

	bool intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2);
}