#pragma once
#include "illumination.hpp"

class PhongBlinn : public Illumination {
public:
	glm::vec3 Illuminate(Point point, Object* obj) override;
	PhongBlinn(float a = 0.25f, float d = 0.55f, float s = 0.30f, int e = 10) : ka(a), kd(d), ks(s), ke(e) {}

private:
	// NOTE: the sum of ka kd ks MUST be equal to 1.0f

	/// <summary>
	/// Ambient scale
	/// </summary>
	float ka;

	/// <summary>
	/// Diffuse scale
	/// </summary>
	float kd;

	/// <summary>
	/// Specular scale
	/// </summary>
	float ks;

	/// <summary>
	/// Exponent of the specular highlight
	/// </summary>
	int ke;
};