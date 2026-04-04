#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <cstdlib>
#include <glm/gtx/polar_coordinates.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "point.hpp"
#include "object.hpp"


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

	/// <summary>
	/// Returns a reflective ray for some direction based on illumination model values
	/// </summary>
	/// <returns></returns>
	Ray virtual ReflectionEquation(Point point) = 0;


// TODO: get rid of ambient color
protected:
	glm::vec3 ambient = glm::vec3(100.0f);
};