#include "Physics.h"
#include "collision.h"

//Intersectiong for point and polygon
bool collision::intersects(const sf::Vector2f point, const sf::VertexArray& polygon)
{
	//Number of vertices in polygon, -1 since last vertex is same as first
	size_t vc = polygon.getVertexCount();
	if (vc == 0) return false;
	size_t n = vc - 1;

	size_t intersectionCount = 0; //If even, no collision. If odd, collision
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y); //Max float value for x, same y as bullet

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
	//-1 for each vertex count since we have an additional vertex to close the shape of polygon
	size_t n1 = poly1.getVertexCount() - 1;
	size_t n2 = poly2.getVertexCount() - 1;

	for (size_t i = 0; i < n1; i++) {
		sf::Vector2f edge = poly1[i].position - poly1[(i + 1) % n1].position;
		sf::Vector2f normal(-edge.y, edge.x);

		//normalize the vector
		float length = sqrt(normal.x * normal.x + normal.y * normal.y);
		normal /= length;

		float min1 = std::numeric_limits<float>::max();
		float max1 = std::numeric_limits<float>::min();
		float min2 = std::numeric_limits<float>::max();
		float max2 = std::numeric_limits<float>::min();

		//Obtain vectors from first polygon
		for (size_t j = 0; j < n1; j++) {
			float projection =
				poly1[j].position.x * normal.x + poly1[j].position.y * normal.y;
			min1 = std::min(min1, projection);
			max1 = std::max(max1, projection);
		}

		//Obtain vectors from second polygon
		for (size_t j = 0; j < n2; j++) {
			float projection =
				poly2[j].position.x * normal.x + poly2[j].position.y * normal.y;
			min2 = std::min(min2, projection);
			max2 = std::max(max2, projection);
		}

		if (max1 < min2 || max2 < min1) {
			return false; //Does not intersect
		}
	}

	return true; //Intersects

}
