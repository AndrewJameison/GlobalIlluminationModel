#pragma once
#include "object.hpp"

class Sphere : public Object {
    public:
        float Intersect(Ray ray) override;

        // Trivial constructor, sends parameters straight to member variables
        Sphere(float r, glm::vec3 c) : radius(r), center(c) {}

    private:
        float radius;
        glm::vec3 center;

};