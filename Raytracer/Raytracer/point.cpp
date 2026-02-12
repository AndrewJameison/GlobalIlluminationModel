#include "point.hpp"
#include "object.hpp"

void Point::AddLight(Light light, glm::vec3 shadow)
{
	lights.push_back(light);
	shadows.push_back(shadow);
}

Point::Point()
{
	distance = INFINITY;
	position = glm::vec3(0.0f), normal = glm::vec3(0.0f), incoming = glm::vec3(0.0f);
}

/// <summary>
/// The constructor for the point class, contains all the information an illumination model will need for calculations
/// </summary>
/// <param name="w">The distance to the point of intersection from the origin</param>
/// <param name="p">The position of the intersection</param>
/// <param name="n">The normal of the object at the point of intersection</param>
/// <param name="obj">The object that has been intersected by the light ray</param>
Point::Point(float w, glm::vec3 p, glm::vec3 n, glm::vec3 i)
{
	distance = w;
	position = p;
	normal = n;
	incoming = i;
}
