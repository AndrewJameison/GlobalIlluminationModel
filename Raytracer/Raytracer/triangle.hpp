#pragma once
#include "object.hpp"

class Triangle : public Object {
  public:
    Point Intersect(Ray ray) override;
    Triangle(glm::vec3 i, glm::vec3 j, glm::vec3 k, sf::Color c);

  private:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};