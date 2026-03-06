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
    glm::vec3 normal = glm::normalize(glm::cross(e1, e2));

    glm::vec3 I = glm::normalize(O - P);

    return Point(w, point, normal, I);

}

Triangle::Triangle(glm::vec3 i, glm::vec3 j, glm::vec3 k, Material* mat, glm::mat4 t)
{
    v0 = i;
    v1 = j;
    v2 = k;
    material = mat;
    LocalT = t;
}

glm::vec2 Triangle::Projector(glm::vec3 intersection)
{
    // TODO: since each vertex is never going to change it's texel value, maybe we can store that information per vertex to speed up calculations on large objects
    
    glm::vec4 i = LocalT * glm::vec4(intersection, 1.0f);

    glm::vec3 local = glm::vec3(i / i.w);

    float u = (intersection.z + 1) / 2.0f;
    float v = (intersection.x + 1) / 2.0f;

    return glm::vec2(u, v);
}
