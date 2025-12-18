// Add this utility function to convert a transformed sf::VertexArray into a std::vector<sf::Vector2f>
inline std::vector<sf::Vector2f> getTransformedPoints(const sf::VertexArray& array, const sf::Transform& transform) {
    std::vector<sf::Vector2f> points;
    for (size_t i = 0; i < array.getVertexCount(); ++i) {
        points.push_back(transform.transformPoint(array[i].position));
    }
    return points;
}