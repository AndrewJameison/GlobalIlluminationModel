#pragma once
#include <glm/glm.hpp>

/// <summary>
/// A wrapper class for the information returned from the point of intersection of a ray
/// </summary>
class Point{
    public:
        float GetDistance() const { return distance; }
        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetNormal() const { return normal; }
        Point(float w, glm::vec3 p, glm::vec3 n): distance(w), position(p), normal(n) {}
    private:
        float distance;
        glm::vec3 position;
        glm::vec3 normal;
};