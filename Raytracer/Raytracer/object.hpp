#pragma once
#include "ray.hpp"
#include "point.hpp"

// NOTE: abstract base classes must be set to a pointer, can not be put on the stack

/// <summary>
/// A parent class for all objects in the world
/// </summary>
class Object abstract {
public:
	glm::vec3 GetDiffuse() const { return diffuse; }
	glm::vec3 GetSpecular() const { return specular; }

	virtual Point Intersect(Ray ray) = 0;
protected:
	glm::vec3 diffuse;
	glm::vec3 specular;
};