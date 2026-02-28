#pragma once
#include "object.hpp"

class Plane : public Object {
public:
	Point Intersect(Ray ray) override;

	Plane(glm::vec3 n,
		glm::mat4 t = glm::mat4(1.0f),
		Material* mat = new PhongMaterial(glm::vec3(100.0f, 0.0f, 0.0f)));

private:
	glm::vec3 origin;
	glm::vec3 normal;
	glm::vec2 Projector(glm::vec3 intersection) override;
};