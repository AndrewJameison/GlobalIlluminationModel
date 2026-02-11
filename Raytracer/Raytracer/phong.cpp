#include "phong.hpp"

glm::vec3 Phong::Illuminate()
{
    return glm::vec3();
}

Phong Phong::phong(float a, float d, float s, float e)
{
    ka = a;
    kd = d;
    ks = s;
    ke = e;

    return Phong();
}
