#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray.hpp"
#include "object.hpp"
#include "light.hpp"

class World {
public:
	void Add(Object* obj);
	glm::vec3 Spawn(Ray ray);
	World(sf::Color bgColor = sf::Color::Blue);
	~World();

private:
	sf::Color ambientColor;
	std::vector<Light*> lights;
	std::vector<Object*> objects;
};