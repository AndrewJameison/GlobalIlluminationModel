#pragma once
#include "object.hpp"

class Sphere : public Object {
public:
	Point Intersect(Ray ray) override;
	Sphere(float r, glm::mat4 t = glm::mat4(1.0f),
		Material* mat = new PhongMaterial(glm::vec3(0.0f, 0.0f, 100.0f)));

private:
	float radius;

	/// <summary>
	/// The origin of the sphere in world space
	/// </summary>
	glm::vec3 origin;
	glm::vec2 Projector(glm::vec3 intersection) override;
};