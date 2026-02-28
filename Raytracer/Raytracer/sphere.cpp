#include "sphere.hpp"
#include <glm/ext/scalar_constants.hpp>

float s = 0.000000001f;
const float PI = glm::pi<float>();

// aka a WHOLE LOT OF MATH
Point Sphere::Intersect(Ray ray)
{
    // See 2-2 cameraRayTracing pg 21

    glm::vec3 O = ray.GetPosition();
    glm::vec3 D = ray.GetDirection();
    float w;
    
    // Step 1: Compute A, B, and C coefficients - A is 1 since D is normalized
    float B = 2.0f * glm::dot(D, (O - origin));

    float C = float(glm::pow(O.x - origin.x, 2) +
                glm::pow(O.y - origin.y, 2) +
                glm::pow(O.z - origin.z, 2) -
                glm::pow(radius, 2));

    // Step 2: Look for b^2 - 4c
    float d = float(glm::pow(B, 2) - 4.0f * C);

    // Step 3: Use the quadratic formula to solve for w values
    if (d < 0)
    {
        // No intersection
        return Point();
    }
    else if (d > -s && d < s)
    {
        // One intersection
        w = -B / 2.0f;
    }
    else
    {
        // Two intersections, take the smaller root
        float root = glm::sqrt(d);
        float w1 = (-B - root) / 2.0f;
        float w2 = (-B + root) / 2.0f;
        w = glm::min(w1, w2);

        if (w < 0.0f)
        {
            w = glm::max(w1, w2);
        }
    }
    if (w < 0)
    {
        // Intersection is behind the film plane
        return Point();
    }

    // Step 4: Calculate the point of intersection
    glm::vec3 P = O + w * D;

    // Step 5: Calculate normal at point of intersection
    glm::vec3 N = glm::normalize(P - origin);

    // Make sure to pass the incoming ray back to the point for the illumination model
    glm::vec3 I = glm::normalize(O - P);

    return Point(w, P, N, I);
}

Sphere::Sphere(float r, glm::mat4 t, Material* mat)
{
    radius = r;
    material = mat;
    LocalT = glm::inverse(t);

    glm::vec4 o = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    origin = glm::vec3(o / o.w);
}

glm::vec2 Sphere::Projector(glm::vec3 intersection)
{
    glm::vec4 i = LocalT * glm::vec4(intersection, 1.0f);

    glm::vec3 local = glm::vec3(i / i.w);

    float phi = glm::acos((local.y) / radius);
    float theta = glm::atan((local.x) / (local.z));

    float u = glm::mod(theta, (2.0f * PI / 2.0f * PI));
    float v = PI - phi / PI;

    return glm::vec2(u, v);
}
