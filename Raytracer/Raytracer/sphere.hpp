#pragma once
#include "object.hpp"

class Sphere : public Object {
    public:
        Point Intersect(Ray ray) override;

        // Trivial constructor, sends parameters straight to member variables
        Sphere(float r, glm::vec3 o, sf::Color c);

    private:
        float radius;
        glm::vec3 origin;

};