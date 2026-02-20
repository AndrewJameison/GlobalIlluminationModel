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

protected:
	Material* material;
};