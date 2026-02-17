#include "phong.hpp"
#include "object.hpp"

glm::vec3 Phong::Illuminate(Point point, Object* obj)
{
    // No intersection, return a background ambient light
    if (obj == nullptr)
    {
        return ka * ambient;
    }

    // The normal of the intersection
    glm::vec3 N = point.GetNormal();

    // Incoming ray direction (initially the camera)
    glm::vec3 V = point.GetIncoming();

    glm::vec3 Ambient = obj->GetDiffuse() * ambient;
        
    glm::vec3 Diffuse = glm::vec3(0.0f);

    glm::vec3 Specular = glm::vec3(0.0f);

    std::vector<Light> lights = point.GetLights();
    std::vector<glm::vec3> shadows = point.GetShadows();

    // The sum diffuse and specular values caused by all light sources not blocked by objects
    // If we cannot see the light from the pointof the intersection, only the ambient light is applied
    for (unsigned int i = 0; i < point.GetLights().size(); i++)
    {
        glm::vec3 L = lights[i].GetIrradiance();

        // Direction of the incoming light
        glm::vec3 S = glm::normalize(shadows[i]);
        float ndots = glm::dot(S, N);
        Diffuse += L * obj->GetDiffuse() * ndots;

        // The perfect mirror reflection of the incoming light
		// NOTE: made the S here negative on a recc. but no noticeable difference
        glm::vec3 R = glm::normalize(glm::reflect(-S, N));
        float rdotv = glm::dot(R, V);
        Specular += L * obj->GetSpecular() * (float)(glm::pow(rdotv, 10));
    }

    return ka * Ambient + kd * Diffuse + ks * Specular;
}
