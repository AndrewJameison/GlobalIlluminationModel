#pragma once
#include "object.hpp"

class Sphere : public Object {
public:
	Point Intersect(Ray ray) override;

	Sphere(float r, glm::vec3 o, Material* mat = new PhongMaterial(glm::vec3(0.0f, 0.0f, 100.0f)));

private:
	float radius;
	glm::vec3 origin;
};