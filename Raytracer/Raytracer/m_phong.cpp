#pragma once
#include "m_phong.hpp"

PhongMaterial::PhongMaterial(glm::vec3 d, glm::vec3 s)
{
	diffuse = d;
	specular = s;
}
