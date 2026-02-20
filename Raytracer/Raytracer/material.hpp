#pragma once
#include <glm/glm.hpp>

// TODO: define some basic Irradiance default values


class Material abstract {
public:
	// Every material should have some diffuse value
	// Based on other factors, the specular value might change as well

	/// <summary>
	/// Calculates the diffuse value of the material at the intersection
	/// </summary>
	/// <param name="obj_pos">The position of the intersection in the object space</param>
	/// <returns></returns>
	virtual glm::vec3 GetDiffuse(glm::vec3 obj_pos = glm::vec3(0.0f)) = 0;
	virtual glm::vec3 GetSpecular() = 0;

protected:
	glm::vec3 specular;
};