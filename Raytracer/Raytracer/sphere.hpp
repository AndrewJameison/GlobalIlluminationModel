#pragma once
#include "object.hpp"

class Sphere : public Object {
public:
	Point Intersect(Ray ray) override;

	Sphere(float r, glm::vec3 o, glm::vec3 d = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 s = glm::vec3(1.0f));

private:
	float radius;
	glm::vec3 origin;
};