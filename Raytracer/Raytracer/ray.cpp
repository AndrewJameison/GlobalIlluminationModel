#include "ray.hpp"

Ray::Ray(glm::vec3 pos, glm::vec3 target)
{
    position = pos;
    direction = glm::normalize(target - pos);
}

