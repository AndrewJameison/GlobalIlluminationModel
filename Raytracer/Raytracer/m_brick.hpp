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
		glm::vec3 b = glm::vec3(0.194f, 0.76f, 0.41f),
		glm::vec3 g = glm::vec3(0.224f, 0.224f, 0.204f),
		glm::vec3 s = glm::vec3(1.0f));
private:
	float brick_width;
	float brick_height;
	float grout_thickness;
	glm::vec3 brick_color;
	glm::vec3 grout_color;
};