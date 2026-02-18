#pragma once
#include "point.hpp"
#include "object.hpp"

// TODO: create a phong Blinn child class of the model (1pt)

// TODO: create a struct to pass along intersection data, not cram it into point

// NOTE: If there is no intersection (point->GetDistance() == INFINITY)...
// ...all illumination models should have a condition to return some 'background' illumination

class Illumination {
public:
	/// <summary>
	/// Calculates the irradiance value of a single point
	/// </summary>
	/// <returns>A vec3 irradiance value from this particular model</returns>
	glm::vec3 virtual Illuminate(Point point, Object* obj) = 0;

protected:
	glm::vec3 ambient = glm::vec3(100.0f);
};