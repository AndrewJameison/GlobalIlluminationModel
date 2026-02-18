#pragma once
#include "illumination.hpp"

class Phong : public Illumination {
public:
	glm::vec3 Illuminate(Point point, Object* obj) override;
	Phong(float a = 0.3f, float d = 0.6f, float s = 0.10f, int e = 8) : ka(a), kd(d), ks(s), ke(e) {}

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