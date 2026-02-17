#include "triangle.hpp"

Point Triangle::Intersect(Ray ray)
{
    // See 2-2 cameraRayTracing pg 33

    glm::vec3 O = ray.GetPosition();
    glm::vec3 D = ray.GetDirection();

    glm::vec3 e1 = v1 - v0;
    glm::vec3 e2 = v2 - v0;
    glm::vec3 T = O - v0;
    glm::vec3 P = glm::cross(D, e2);
    glm::vec3 Q = glm::cross(T, e1);

    float det = glm::dot(P, e1);

    // Ray is parallel to triangle, no intersection
    if (!det)
    {
        return Point();
    }

    glm::vec3 result = glm::vec3(glm::dot(Q, e2), 
                                 glm::dot(P, T),
                                 glm::dot(Q, D)) / det;

    float w = result.x;
    float u = result.y;
    float v = result.z;

    // Intersection is behind ray origin
    if (w < 0.0f)
    {
        return Point();
    }

    // Intersection is outside of triangle
    if (u < 0.0f || v < 0.0f || u + v > 1.0f)
    {
        return Point();
    }

    glm::vec3 point = O + w * D;
    glm::vec3 normal = glm::cross(e1, e2);

    glm::vec3 I = glm::normalize(O - P);

    return Point(w, point, normal, I);

}

Triangle::Triangle(glm::vec3 i, glm::vec3 j, glm::vec3 k, glm::vec3 d, glm::vec3 s)
{
    v0 = i;
    v1 = j;
    v2 = k;
    diffuse = d;
    specular = s;
}
