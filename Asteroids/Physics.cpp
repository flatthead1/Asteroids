#include "Physics.h"

bool collision::intersects(const sf::Vector2f point, const sf::VertexArray& polygon)
{
	//Number of vertices in polygon, -1 since last vertex is same as first
	size_t vc = polygon.getVertexCount();
	if (vc < 2) return false;
	if (vc == 0) return false;
	size_t n = vc - 1;

	size_t intersectionCount = 0; //If even, no collision. If odd, collision
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y); //Max float value for x, same y as bullet

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
sf::VertexArray collision::getTransformedPolygon(const sf::VertexArray& polygon, const sf::Transform& transform)
{
	sf::VertexArray transformed = polygon;

	for (size_t i = 0; i < transformed.getVertexCount(); i++)
	{
		//Transform each vertex position
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}
