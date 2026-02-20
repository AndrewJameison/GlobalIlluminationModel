#include "phong-blinn.hpp"
#include "object.hpp"

glm::vec3 PhongBlinn::Illuminate(Point point, Object* obj)
{
    // No intersection, return a background ambient light
    if (obj == nullptr)
    {
        return ambient;
    }

    Material* material = obj->GetMaterial();

    // The normal of the intersection
    glm::vec3 N = point.GetNormal();

    // Incoming ray direction (initially the camera)
    glm::vec3 V = point.GetIncoming();

    glm::vec3 Ambient = material->GetDiffuse() * ambient;

    glm::vec3 Diffuse = glm::vec3(0.0f);

    glm::vec3 Specular = glm::vec3(0.0f);

    std::vector<Light> lights = point.GetLights();
    std::vector<glm::vec3> shadows = point.GetShadows();

    // The sum diffuse and specular values caused by all light sources not blocked by objects
    // If we cannot see the light from the point of the intersection, only the ambient light is applied
    for (unsigned int i = 0; i < point.GetLights().size(); i++)
    {
        glm::vec3 L = lights[i].GetIrradiance();

        // Direction of the incoming light
        glm::vec3 S = glm::normalize(shadows[i]);
        Diffuse += L * material->GetDiffuse() * glm::dot(S, N);

		// The half-way vector between the incoming light and the viewer

        // TODO: Fix the weird edge highlights around the diffuse section
        glm::vec3 H = glm::normalize(S + V);
        Specular += L * material->GetSpecular() * (float)(glm::pow(glm::dot(H, N), ke));
    }

    return ka * Ambient + kd * Diffuse + ks * Specular;
}