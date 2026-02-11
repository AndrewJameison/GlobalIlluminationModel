#include "light.hpp"

Light::Light(glm::vec3 o, glm::vec3 irr)
{
	origin = o;
	irradiance = irr;
}
