#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray.hpp"
#include "object.hpp"
#include "light.hpp"
#include "illumination.hpp"

class World {
public:
	void Add(Object* obj);
	void Add(Light* light);
	glm::vec3 Spawn(Ray ray);
	World(Illumination* lightModel);
	~World();

private:
	Illumination* model;
	std::vector<Light*> lights;
	std::vector<Object*> objects;
};