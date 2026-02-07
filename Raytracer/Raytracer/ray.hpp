#pragma once
#include <glm/glm.hpp>

class Ray {
    public:
        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetDirection() const { return direction; }
        Ray(glm::vec3 pos, glm::vec3 target);

    private:
        glm::vec3 position;
        glm::vec3 direction;
};