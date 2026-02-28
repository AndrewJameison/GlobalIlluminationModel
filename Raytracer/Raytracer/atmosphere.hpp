#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>


class Atmosphere
{
public:
    Atmosphere(glm::vec3 sd = glm::vec3(0.0f, 1.0f, 0.0f), 
        float er = 6360e3, float ar = 6420e3, float hr = 7994, float hm = 1200) :
        sunDirection(sd), earthRadius(er), atmosphereRadius(ar), Hr(hr), Hm(hm) { }

    glm::vec3 computeIncidentLight(const glm::vec3& orig, const glm::vec3& dir, float tmin, float tmax) const;

    glm::vec3 sunDirection;      //The sun direction (normalized) 
    float earthRadius;       //In the paper this is usually Rg or Re (radius ground, eart) 
    float atmosphereRadius;  //In the paper this is usually R or Ra (radius atmosphere) 
    float Hr;                //Thickness of the atmosphere if density was uniform (Hr) 
    float Hm;                //Same as above but for Mie scattering (Hm) 

    static const glm::vec3 betaR;
    static const glm::vec3 betaM;
};

const glm::vec3 Atmosphere::betaR(3.8e-6f, 13.5e-6f, 33.1e-6f);
const glm::vec3 Atmosphere::betaM(21e-6f);