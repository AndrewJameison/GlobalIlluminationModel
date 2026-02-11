#pragma once
#include "illumination.hpp"

class Phong : Illumination {
	// TODO: add Phong parameters
	// ka ambient scale
	// kd diffuse scale
	// ks specular scale
	// kd +ks < 1 see assn-3 pg11
	// exponent ke (size of the specular highlight)
	// L(V) = 

public:
	glm::vec3 Illuminate() override;
	Phong phong(float a, float d, float s, float e);

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
	float ke;
};