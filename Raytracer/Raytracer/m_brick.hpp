#pragma once
#include "material.hpp"

/// <summary>
/// A procedurally generated brick texture
/// </summary>
class BrickMaterial : public Material {
public:
	glm::vec3 GetDiffuse(glm::vec2 uv) override;
	glm::vec3 GetSpecular() override { return specular; }

	BrickMaterial(float kr, float kt, float w = 3.0f, float h = 1.0f, float t = 0.2f,
		glm::vec3 b = glm::vec3(19.4f, 7.6f, 4.1f),
		glm::vec3 g = glm::vec3(22.4f, 22.4f, 20.4f),
		glm::vec3 s = glm::vec3(100.0f));
private:
	float brick_width;
	float brick_height;
	float grout_thickness;
	glm::vec3 brick_color;
	glm::vec3 grout_color;
};