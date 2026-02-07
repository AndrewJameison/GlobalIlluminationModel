#pragma once
#include "object.hpp"

class Triangle : public Object {
  public:
    float Intersect(Ray ray) override;
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) : v0(a), v1(b), v2(c) {}

  private:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};