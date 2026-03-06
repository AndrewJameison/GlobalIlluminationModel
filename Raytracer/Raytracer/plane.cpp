#include "plane.hpp"

Point Plane::Intersect(Ray ray)
{
    float den = glm::dot(ray.GetDirection(), normal);

    // Ray parallel to the plane
    // NOTE: If we only wanted light to reflect off of the "right" side of the normal...
    // ...we should only use negative denominator values
    if (den == 0.0f)
    {
        return Point();
    }

    float num = (glm::dot(origin - ray.GetPosition(), normal));

    float w = num / den;

    // Intersection behind the ray
    if (w <= 0)
    {
        return Point();
    }

    glm::vec3 O = ray.GetPosition();

    glm::vec3 P = O + w * ray.GetDirection();

    glm::vec3 I = glm::normalize(O - P);

    return Point(w, P, normal, I);
}

Plane::Plane(glm::vec3 n, glm::mat4 t, Material* mat)
{
    normal = n;
    material = mat;
    LocalT = t;

    glm::vec4 o = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    origin = glm::vec3(o / o.w);
}

glm::vec2 Plane::Projector(glm::vec3 intersection)
{
    glm::vec4 i = LocalT * glm::vec4(intersection, 1.0f);

    glm::vec3 local = glm::vec3(i / i.w);

    float u = (local.z + 1) / 2.0f;
    float v = (local.x + 1) / 2.0f;

    return glm::vec2(u, v);
}

