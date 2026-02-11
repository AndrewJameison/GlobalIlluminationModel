#pragma once
#include <glm/glm.hpp>

class Illumination {
public:
	/// <summary>
	/// Calculates the irradiance value of a single point
	/// </summary>
	/// <returns>A vec3 irradiance value from this particular model</returns>
	virtual glm::vec3 Illuminate() = 0;


protected:
	// TODO: Ask for a bunch of information, return some irradiance value
};