#pragma once
#include "illumination.hpp"

class Phong : public Illumination {
// kd +ks < 1 see assn-3 pg11
public:
	glm::vec3 Illuminate(Point point, Object* obj) override;
	Phong(float a = 0.5f, float d = 0.25f, float s = 0.25f, int e = 8) : ka(a), kd(d), ks(s), ke(e) {}

private:
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