#include "atmosphere.hpp"

Atmosphere::Atmosphere(glm::vec3 sd, float er, float ar, float hr, float hm)
{
    glm::vec3 sunDirection = sd;  
    float earthRadius = er;
    float atmosphereRadius = ar;
    float Hr = ar;
    float Hm = hm;

    planet = new Sphere(earthRadius);
    atmosphere = new Sphere(atmosphereRadius);
}

glm::vec3 Atmosphere::computeIncidentLight(Ray ray, float tmin, float tmax)
{
    //float t0 = 0.0f, t1 = 0.0f;

    //if (!IntersectPlanet(ray, t0, t1) || t1 < 0) return 0;
    Point pt = atmosphere->Intersect(ray);
    float w = pt.GetDistance();
    if (w == INFINITY)
    {
        // TODO: implement lighting from outside of the atmosphere
        return glm::vec3(0.0f);
    }

    // TODO: try from the inside of a sphere

    glm::vec3 rayDir = ray.GetDirection();
    glm::vec3 originPos = ray.GetPosition();

    uint32_t numSamples = 16;
    uint32_t numSamplesLight = 8;
    float segmentLength = (tmax - tmin) / numSamples;
    float tCurrent = tmin;
    glm::vec3 sumR(0), sumM(0);  // mie and rayleigh contribution 
    float opticalDepthR = 0, opticalDepthM = 0;
    float mu = dot(ray.GetDirection(), sunDirection);  // mu in the paper which is the cosine of the angle between the sun direction and the ray direction 
    float phaseR = 3.f / (16.f * glm::pi<float>() * (1 + mu * mu));
    float g = 0.76f;
    float phaseM = 3.f / (8.f * glm::pi<float>()) * ((1.f - g * g) * (1.f + mu * mu)) / ((2.f + g * g) * pow(1.f + g * g - 2.f * g * mu, 1.5f));

    for (uint32_t i = 0; i < numSamples; ++i) {
        glm::vec3 samplePosition = originPos + (tCurrent + segmentLength * 0.5f) * rayDir;
        float height = samplePosition.length() - earthRadius;
        // compute optical depth for light
        float hr = exp(-height / Hr) * segmentLength;
        float hm = exp(-height / Hm) * segmentLength;
        opticalDepthR += hr;
        opticalDepthM += hm;
        // light optical depth
        //float t0Light = 0.0f, t1Light = 0.0f;
        
        Ray sampleDir(samplePosition, sunDirection);
        //IntersectPlanet(sampleDir, t0Light, t1Light);
        Point pt = atmosphere->Intersect(sampleDir);

        float segmentLengthLight = pt.GetDistance() / numSamplesLight, tCurrentLight = 0;
        float opticalDepthLightR = 0, opticalDepthLightM = 0;
        uint32_t j;

        for (j = 0; j < numSamplesLight; ++j) {
            glm::vec3 samplePositionLight = samplePosition + (tCurrentLight + segmentLengthLight * 0.5f) * sunDirection;
            float heightLight = samplePositionLight.length() - earthRadius;
            if (heightLight < 0) break;
            opticalDepthLightR += exp(-heightLight / Hr) * segmentLengthLight;
            opticalDepthLightM += exp(-heightLight / Hm) * segmentLengthLight;
            tCurrentLight += segmentLengthLight;
        }

        if (j == numSamplesLight) {
            glm::vec3 tau = betaR * (opticalDepthR + opticalDepthLightR) + betaM * 1.1f * (opticalDepthM + opticalDepthLightM);
            glm::vec3 attenuation(exp(-tau.x), exp(-tau.y), exp(-tau.z));
            sumR += attenuation * hr;
            sumM += attenuation * hm;
        } 

        tCurrent += segmentLength; 
    } 
 
    // We use a magic number here for the intensity of the sun (20). We will make it more
    // scientific in a future revision of this lesson/code
    return (sumR * betaR * phaseR + sumM * betaM * phaseM) * 20000.0f; 
}
