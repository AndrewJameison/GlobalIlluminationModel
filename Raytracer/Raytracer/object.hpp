#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>
#include "ray.hpp"

class Object {
  public:
    sf::Color color;

    // NOTE: For whatever reason, the intersect function can only be overriden if you assign it to a point. Trying to instantiate on the stack throws C2259
    float virtual Intersect(Ray ray) = 0; // Only consider intersections if they are in front of the film plane
  private:
};