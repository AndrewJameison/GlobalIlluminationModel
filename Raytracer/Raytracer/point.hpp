#pragma once
#include <glm/glm.hpp>
#include "light.hpp"

/// <summary>
/// A wrapper class for the information returned from the point of intersection of a ray
/// </summary>
class Point {
public:
	void AddLight(Light* light, glm::vec3 lightDir);
	float GetDistance() const { return distance; }
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetNormal() const { return normal; }
	Point(float w, glm::vec3 p, glm::vec3 n) : distance(w), position(p), normal(n) {}
	Point() : distance(INFINITY), position(glm::vec3(0.0f)), normal(glm::vec3(0.0f)) {}
private:
	float distance;
	std::vector<Light*> lights;
	std::vector<glm::vec3> lightDirections;
	glm::vec3 position;
	glm::vec3 normal;
};