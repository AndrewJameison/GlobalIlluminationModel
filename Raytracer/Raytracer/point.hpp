#pragma once
#include <glm/glm.hpp>


// TODO: replace intersect return value with Point class
// TODO: restructure class variables and methods to optimize mem use

class Point{
    public:
        Point(glm::vec3 p, glm::vec3 n, float w): position(p), normal(n), magnitude(w) {}
        
        float GetMagnitude() { return magnitude; }
        glm::vec3 GetPosition() { return position; }
        glm::vec3 GetNormal() { return normal; }
    private:
        float magnitude;
        glm::vec3 position;
        glm::vec3 normal;
};