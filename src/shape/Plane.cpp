#include "Plane.hpp"

Plane::Plane(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third)
	: first(first, 0.0f), second(second, 0.0f), third(third, 0.0f)
{}

void Plane::transform(const glm::mat4 &trans)
{
	first = trans * first;
	second = trans * second;
	third = trans * third;
}

glm::vec3 cramersRule(const glm::mat3 &matrix, const glm::vec3 &b)
{

}

bool Plane::collides(const glm::vec3 &position, const glm::vec3 &direction, float &distance)
{
	glm::vec3 p1 = second - first; // plane direction 1
	glm::vec3 p2 = third - first; // plane direction 2
	glm::vec3 b = position - first;
}
