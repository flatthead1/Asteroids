#pragma once

#include <SFML/Graphics.hpp>

namespace collision {
	bool intersects(const sf::Vector2f point, const sf::VertexArray& polygon);
	sf::VertexArray getTransformedPolygon(const sf::VertexArray& polygon, const sf::Transform& transform);
}