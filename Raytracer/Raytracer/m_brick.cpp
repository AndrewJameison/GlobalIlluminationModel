#include "m_brick.hpp"

glm::vec3 BrickMaterial::GetDiffuse(glm::vec2 uv)
{
    float u = uv.x;
    float v = uv.y;

    // Find the texel value of the given uv coordinates
    float uu = u / (brick_width + grout_thickness);
    float vv = v / (brick_height + grout_thickness);

    if (glm::mod(vv*0.5f, 1.0f) > 0.5f)
    {
        uu += 0.5f;
    }

    int uBrick = glm::floor(uu);
    int vBrick = glm::floor(vv);

    uu -= uBrick;
    vv -= vBrick;

    if ((uu < grout_thickness) || (vv < grout_thickness))
    {
        return grout_color;
    }
    else
    {
        return brick_color;
    }
}

BrickMaterial::BrickMaterial(float w, float h, float t, glm::vec3 b, glm::vec3 g, glm::vec3 s)
{
    brick_width = w;
    brick_height = h;
    grout_thickness = t;

    brick_color = b;
    grout_color = g;
    specular = s;
}
