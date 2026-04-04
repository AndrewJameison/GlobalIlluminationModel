#pragma once
#include "material.hpp"

class PhongMaterial : public Material {
public:
	glm::vec3 GetDiffuse(glm::vec2 uv) override { return diffuse; }
	glm::vec3 GetSpecular() override { return specular; }

	PhongMaterial(float kr, float kt, glm::vec3 d = glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3 s = glm::vec3(100.0f));

private:
	glm::vec3 diffuse;
};