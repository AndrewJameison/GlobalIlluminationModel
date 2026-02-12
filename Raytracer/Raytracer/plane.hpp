#pragma once
#include "object.hpp"

class Plane : public Object {
public:
	Point Intersect(Ray ray) override;
	Plane(glm::vec3 o, glm::vec3 n, glm::vec3 d, glm::vec3 s);

private:
	glm::vec3 origin;
	glm::vec3 normal;
};