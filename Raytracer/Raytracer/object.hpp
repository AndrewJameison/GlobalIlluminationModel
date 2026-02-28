#pragma once
#include "ray.hpp"
#include "point.hpp"
#include "m_phong.hpp"

// NOTE: abstract base classes must be set to a pointer, can not be put on the stack

/// <summary>
/// A parent class for all objects in the world
/// </summary>
class Object abstract {
public:
	Material* GetMaterial() const { return material; }

	virtual Point Intersect(Ray ray) = 0;
	
	/// <summary>
	/// Moves local coordinates into uv space
	/// </summary>
	/// <param name="intersection">The global coordinates of the intersection</param>
	/// <returns>Texture space UV coordinates</returns>
	virtual glm::vec2 Projector(glm::vec3 intersection) = 0;

protected:
	/// <summary>
	/// Transforms world coordinates into local space
	/// </summary>
	glm::mat4 LocalT;

	Material* material;
};