#include "m_checker.hpp"

glm::vec3 CheckersMaterial::GetDiffuse(glm::vec2 uv)
{
    // TODO: should check_width be a world space value? It feels inconsistent between objects

    // TODO: add anti-aliasing to the checker matt

    float u = uv.x;
    float v = uv.y; 

    // Find the texel value of the given uv coordinates
    int uu = int(std::floor(u / checker_width)) % 2;
    int vv = int(std::floor(v / checker_width)) % 2;

    if ((uu + vv) % 2)
    {
        return brick_color_1;
    }
    else
    {
        return brick_color_2;
    }
}

CheckersMaterial::CheckersMaterial(float kr, float kt, float w, glm::vec3 b1, glm::vec3 b2, glm::vec3 s)
{
    reflectance = kr;
    transmission = kt;
    checker_width = w;
    brick_color_1 = b1;
    brick_color_2 = b2;
    specular = s;
}
