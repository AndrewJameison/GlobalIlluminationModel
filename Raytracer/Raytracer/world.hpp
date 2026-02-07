#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ray.hpp"
#include "object.hpp"

class World {
  public:
    void Add(Object* obj);
    sf::Color Spawn(Ray ray);
    World(sf::Color bgColor = sf::Color::Black);
    ~World();
  
  private:
    sf::Color backgroundColor;
    std::vector<Object*> objects;
};