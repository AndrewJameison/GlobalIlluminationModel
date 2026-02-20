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

Plane::Plane(glm::vec3 o, glm::vec3 n, Material* mat)
{
    origin = o;
    normal = n;
    material = mat;
}

