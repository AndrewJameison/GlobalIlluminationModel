#pragma once
#include "object.hpp"

class Triangle : public Object {
public:
    Point Intersect(Ray ray) override;
    Triangle(glm::vec3 i, glm::vec3 j, glm::vec3 k, 
        Material* mat = new PhongMaterial(glm::vec3(100.0f, 0.0f, 0.0f)));

private:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};