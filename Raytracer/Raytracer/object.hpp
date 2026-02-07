#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>
#include "ray.hpp"
#include "point.hpp"

/// <summary>
/// A parent class for all objects in the world
/// </summary>
class Object {
  public:
    sf::Color color;

    // NOTE: For whatever reason, the intersect function can only be overriden if you assign it to a point. Trying to instantiate on the stack throws C2259
    Point virtual Intersect(Ray ray) = 0; // Only consider intersections if they are in front of the film plane
  protected:
      /// <summary>
      /// A NULL equivalent return value for Objects to indicate no intersection 
      /// </summary>
      const Point ZERO = Point(INFINITY, glm::vec3(0.0f), glm::vec3(0.0f));
};