#include "plane.hpp"

Point Plane::Intersect(Ray ray)
{
    float den = glm::dot(ray.GetDirection(), normal);

    // Ray parallel to the plane
    // NOTE: If we only wanted light to reflect off of the "right" side of the normal...
    // ...we should only use negative denominator values
    if (den == 0.0f)
    {
        return Object::ZERO;
    }

    float num = (glm::dot(origin - ray.GetPosition(), normal));

    float w = num / den;

    // Intersection behind the ray
    if (w <= 0)
    {
        return Object::ZERO;
    }

    glm::vec3 P = ray.GetPosition() + w * ray.GetDirection();

    return Point(w, P, normal);
}

Plane::Plane(glm::vec3 o, glm::vec3 n, sf::Color c)
{
    origin = o;
    normal = n;
    color = c;
}

