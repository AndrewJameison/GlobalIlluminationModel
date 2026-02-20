#include "m_checker.hpp"

glm::vec3 CheckersMaterial::GetDiffuse(glm::vec3 obj_pos)
{
    // The whole uv thing
    return glm::vec3();
}

CheckersMaterial::CheckersMaterial(float w, glm::vec3 b1, glm::vec3 b2, glm::vec3 s)
{
    checker_width = w;
    brick_color_1 = b1;
    brick_color_2 = b2;
    specular = s;
}
