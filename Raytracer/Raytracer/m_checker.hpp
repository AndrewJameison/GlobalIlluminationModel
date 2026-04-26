#pragma once
#include "material.hpp"

/// <summary>
/// A procedurally generated 
/// </summary>
class CheckersMaterial : public Material {
public:
	glm::vec3 GetDiffuse(glm::vec2 uv) override;
	glm::vec3 GetSpecular() override { return specular; }

	CheckersMaterial(float kr, float kt, float w = 1.0f,
					glm::vec3 b1 = glm::vec3(256.0f, 256.0f, 0.0f), 
					glm::vec3 b2 = glm::vec3(256.0f, 0.0f, 0.0f), 
					glm::vec3 s = glm::vec3(256.0f));
private:
	float checker_width;
	glm::vec3 brick_color_1;
	glm::vec3 brick_color_2;
};