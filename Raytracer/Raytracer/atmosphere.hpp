#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "ray.hpp"
#include "sphere.hpp"

// TODO: implement multi scattering
// TODO: Do NOT implement multi scattering

class Atmosphere
{
public:
    ~Atmosphere();
    Atmosphere(float irr = 200000.0f, float degrees = 0.0f, glm::vec3 rot_axis = glm::vec3(1.0f, 0.0f, 0.0f),
        float er = 6360e3f, float ar = 6420e3f, float hr = 7994.0f, float hm = 1200.0f);

    //float er = 6360e3f, float ar = 6420e3f, float hr = 7994.0f, float hm = 1200.0f);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="tmin"></param>
    /// <param name="tmax"></param>
    /// <returns></returns>
    glm::vec3 computeIncidentLight(Ray ray, float tmin, float tmax) const;

    Point IntersectPlanet(Ray ray) { return planet->Intersect(ray); }
private:
    glm::vec3 sunDirection;  //The sun direction (normalized) 
    float irradiance;
    float earthRadius;       //In the paper this is usually Rg or Re (radius ground, eart) 
    float atmosphereRadius;  //In the paper this is usually R or Ra (radius atmosphere) 
    float Hr;                //Thickness of the atmosphere if density was uniform (Hr) 
    float Hm;                //Same as above but for Mie scattering (Hm) 

    Sphere* planet;
    Sphere* atmosphere;
};

//static const glm::vec3 betaR(3.8e-6f, 13.5e-6f, 33.1e-6f);
//static const glm::vec3 betaM(21e-6f);

static const glm::dvec3 betaR(3.8e-6f, 13.5e-6f, 33.1e-6f);
static const glm::dvec3 betaM(21e-6f);