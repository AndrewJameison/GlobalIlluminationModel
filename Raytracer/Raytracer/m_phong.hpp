#pragma once
#include "material.hpp"

class PhongMaterial : public Material {
public:
	glm::vec3 GetDiffuse(glm::vec3 obj_pos) override { return diffuse; }
	glm::vec3 GetSpecular() override { return specular; }

	PhongMaterial(glm::vec3 d, glm::vec3 s = glm::vec3(100.0f));

private:
	glm::vec3 diffuse;
};