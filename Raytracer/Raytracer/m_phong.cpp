#pragma once
#include "m_phong.hpp"

PhongMaterial::PhongMaterial(float kr, float kt, glm::vec3 d, glm::vec3 s)
{
	reflectance = kr;
	transmission = kt;
	diffuse = d;
	specular = s;
}
