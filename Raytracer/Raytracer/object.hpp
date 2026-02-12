#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>
#include "ray.hpp"
#include "point.hpp"

/// <summary>
/// A parent class for all objects in the world
/// </summary>
class Object abstract {
public:
	/// <summary>
	/// A NULL equivalent return value for Objects to indicate no intersection 
	/// </summary>

	glm::vec3 GetDiffuse() const { return diffuse; }
	glm::vec3 GetSpecular() const { return specular; }

	//const Point ZERO = Point(INFINITY, glm::vec3(), glm::vec3(), glm::vec3());//, nullptr);

	// NOTE: For whatever reason, the intersect function can only be overriden if you assign it to a pointer. Trying to instantiate on the stack throws C2259
	virtual Point Intersect(Ray ray);
protected:
	glm::vec3 diffuse;
	glm::vec3 specular;
};