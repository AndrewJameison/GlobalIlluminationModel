#pragma once
#include <glm/glm.hpp>
#include "Point.hpp"

// TODO: create a phong Blinn child class of the model (1pt)

// NOTE: If there is no intersection (point->GetDistance() == INFINITY)...
// ...all illumination models should have a condition to return some 'background' illumination

class Illumination {
public:
	/// <summary>
	/// Calculates the irradiance value of a single point
	/// </summary>
	/// <returns>A vec3 irradiance value from this particular model</returns>
	glm::vec3 virtual Illuminate(Point point) = 0;

protected:
	glm::vec3 ambient;
};