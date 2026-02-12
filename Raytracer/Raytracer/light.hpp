#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>

class Light {
public:
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetIrradiance() const { return irradiance; }
	Light(glm::vec3 pos, glm::vec3 irr);
private:
	glm::vec3 position;
	glm::vec3 irradiance;
};