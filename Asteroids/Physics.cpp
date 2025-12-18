#include "Physics.h"
#include "collision.h"
#include <limits>
#include <cmath>

//Intersectiong for point and polygon
bool collision::intersects(const sf::Vector2f point, const sf::VertexArray& polygon)
{
	//Number of vertices in polygon, -1 since last vertex is same as first
	size_t vc = polygon.getVertexCount();
	if (vc == 0) return false;
	size_t n = vc - 1;

	size_t intersectionCount = 0; //If even, no collision. If odd, collision
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::infinity(), point.y); //Max float value for x, same y as bullet

	//Check each edge of polygon for intersection with ray
	for (size_t i = 0; i < n; i++)
	{
		//Get points of current polygon edge
		sf::Vector2f p1 = polygon[i].position;
		sf::Vector2f p2 = polygon[(i + 1) % n].position;

		//Check on y-axis if edge crosses ray
		if ((p1.y < point.y && p2.y >= point.y) || (p2.y < point.y && p1.y >= point.y))
		{
			float t = (point.y - p1.y) / (p2.y - p1.y);
			float intersectX = p1.x + t * (p2.x - p1.x);

			//Only if the check on y-axis passes, check on x-axis similarly
			if (intersectX <= point.x && intersectX <= rayEnd.x)
			{
				intersectionCount++;
			}
		}
	}

	//If odd number of intersections, bullet is inside asteroid polygon
	return (intersectionCount % 2 == 1);
}

//Apply transformation to polygon and return transformed polygon
sf::VertexArray collision::getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform)
{
	sf::VertexArray transformed = polygon;

	for (size_t i = 0; i < transformed.getVertexCount(); i++)
	{
		//Transform each vertex position
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}

//Intersection for VertexArrays against each other
bool collision::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2)
{

	if (poly1.getVertexCount() < 2 || poly2.getVertexCount() < 2) return false;
	size_t n1 = poly1.getVertexCount() - 1;
	size_t n2 = poly2.getVertexCount() - 1;

	auto testAxesFrom = [](const sf::VertexArray& A, const sf::VertexArray& B, size_t aCount, size_t bCount) -> bool {
		for (size_t i = 0; i < aCount; ++i) {
			//Edge from i -> i+1
			sf::Vector2f p1 = A[i].position;
			sf::Vector2f p2 = A[(i + 1) % aCount].position;
			sf::Vector2f edge = p2 - p1;
			//Perpendicular
			sf::Vector2f axis(-edge.y, edge.x);

			//Skip edges with no length
			float axisLen = std::sqrt(axis.x * axis.x + axis.y * axis.y);
			if (axisLen == 0.0f) continue;
			axis.x /= axisLen;
			axis.y /= axisLen;

			float minA = std::numeric_limits<float>::infinity();
			float maxA = -std::numeric_limits<float>::infinity();
			float minB = std::numeric_limits<float>::infinity();
			float maxB = -std::numeric_limits<float>::infinity();

			//Projection for A
			for (size_t j = 0; j < aCount; ++j) {
				float proj = A[j].position.x * axis.x + A[j].position.y * axis.y;
				minA = std::min(minA, proj);
				maxA = std::max(maxA, proj);
			}

			//Projection for B
			for (size_t j = 0; j < bCount; ++j) {
				float proj = B[j].position.x * axis.x + B[j].position.y * axis.y;
				minB = std::min(minB, proj);
				maxB = std::max(maxB, proj);
			}

			// If projections do not overlap, there is a separating axis -> no intersection
			if (maxA < minB || maxB < minA) return false;
		}
		return true; //No separating axis found
	};

	//Test axes from both polygons
	if (!testAxesFrom(poly1, poly2, n1, n2)) return false;
	if (!testAxesFrom(poly2, poly1, n2, n1)) return false;

	return true; //Confirmed intersection
}
