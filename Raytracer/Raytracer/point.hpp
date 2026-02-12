#pragma once
#include <glm/glm.hpp>
#include "light.hpp"
#include "object.hpp"

/// <summary>
/// A wrapper class for the information returned from the point of intersection of a ray
/// </summary>
class Point {
public:

	void AddLight(Light* light, glm::vec3 shadow);

	// Public Getters
	float GetDistance() const { return distance; }
	//Object* GetObject() const { return object; }
	//Object* object;
	glm::vec3 GetIncoming() const { return incoming; }
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetNormal() const { return normal; }
	std::vector<Light*> GetLights() const { return lights; }
	std::vector<glm::vec3> GetShadows() const { return shadows; }

	Point();
	Point(float w, glm::vec3 p, glm::vec3 n, glm::vec3 i);//, Object* obj);

private:
	float distance;
	glm::vec3 incoming;
	glm::vec3 position;
	glm::vec3 normal;
	std::vector<Light*> lights;
	std::vector<glm::vec3> shadows;
};