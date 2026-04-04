#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray.hpp"
#include "object.hpp"
#include "light.hpp"
#include "illumination.hpp"
#include "atmosphere.hpp"

class World {
public:
	void Add(Object* obj);
	void Add(Light light);
	glm::vec3 Spawn(int depth, Ray ray);
	World(Illumination* lightModel, Atmosphere* atmo);
	~World();

private:
	/// <summary>
	/// The recursive depth constant 
	/// </summary>
	const int MAX_DEPTH = 1;
	const glm::vec3 BACKGROUND_COLOR = glm::vec3(53.7f, 81.2f, 94.1f) * 150.f;

	glm::vec3 PerfectReflection(int depth, float kr, Ray ray, Point intersection);
	glm::vec3 MonteCarloReflection(int depth, int samples, float kr, Point intersection);

	Illumination* model;
	Atmosphere* atmosphere;
	std::vector<Light> lights;
	std::vector<Object*> objects;
};