#pragma once
#include <glm/glm.hpp>

// TODO: define some basic Irradiance default values

class Material abstract {
public:
	// Every material should have some diffuse value
	// Based on other factors, the specular value might change as well

	/// <summary>
	/// Calculates the diffuse value of the material
	/// </summary>
	/// <param name="uv">The uv coordinates of the material</param>
	/// <returns></returns>
	virtual glm::vec3 GetDiffuse(glm::vec2 uv) = 0;
	virtual glm::vec3 GetSpecular() = 0;

protected:
	glm::vec3 specular;
};