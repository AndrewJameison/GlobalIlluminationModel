#include "point.hpp"

void Point::AddLight(Light* light, glm::vec3 lightDir)
{
	lights.push_back(light);
	lightDirections.push_back(lightDir);
}
