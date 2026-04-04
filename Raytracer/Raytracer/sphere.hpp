#pragma once
#include "object.hpp"

// TODO: move get position to several accessor functions in object, all objects should be able to return a transform of some kind

class Sphere : public Object {
public:
	Point Intersect(Ray ray) override;
	glm::vec3 GetPosition() const { return origin; }
	Sphere(float r, glm::mat4 t = glm::mat4(1.0f),
		Material* mat = new PhongMaterial(0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 100.0f)));

private:
	float radius;

	/// <summary>
	/// The origin of the sphere in world space
	/// </summary>
	glm::vec3 origin;
	glm::vec2 Projector(glm::vec3 intersection) override;
};