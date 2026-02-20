#pragma once
#include "material.hpp"

/// <summary>
/// A procedurally generated 
/// </summary>
class CheckersMaterial : public Material {
public:
	glm::vec3 GetDiffuse(glm::vec3 obj_pos) override;
	glm::vec3 GetSpecular() override { return specular; }

	CheckersMaterial(float w = 10.0f,
					glm::vec3 b1 = glm::vec3(100.0f, 100.0f, 0.0f), 
					glm::vec3 b2 = glm::vec3(100.0f, 0.0f, 0.0f), 
					glm::vec3 s = glm::vec3(100.0f));
private:
	float checker_width;
	glm::vec3 brick_color_1;
	glm::vec3 brick_color_2;
};