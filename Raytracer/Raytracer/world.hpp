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
	const int MAX_DEPTH = 5;

	const float AIR_INDEX_REFRACTION = 1.0f;
	
	const glm::vec3 BACKGROUND_COLOR = glm::vec3(0.537f, 0.812f, 0.941f);// *0.55f;

	Ray Reflection(Ray ray, Point intersection);
	Ray Transmission(float kt, Ray ray, Point intersection);

	Illumination* model;
	Atmosphere* atmosphere;
	std::vector<Light> lights;
	std::vector<Object*> objects;
};