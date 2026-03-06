#include "atmosphere.hpp"
#include <glm/ext/matrix_transform.hpp>

Atmosphere::~Atmosphere()
{
    delete planet;
    delete atmosphere;
}

Atmosphere::Atmosphere(float irr, float rot, glm::vec3 rot_axis, float er, float ar, float hr, float hm)
{
    irradiance = irr;

    glm::mat4 test = glm::rotate(glm::mat4(1.0f), rot, rot_axis);
    glm::vec4 thing = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) * test;

    sunDirection = glm::vec3(thing) / thing.w;  
    earthRadius = er;
    atmosphereRadius = ar;
    Hr = hr;
    Hm = hm;

    // TODO: right now, we just want the camera to be 'generally' on the surface of the planet.
    const glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 earthPosition = glm::translate(I, glm::vec3(0.0f, -earthRadius - 1000.0f, 0.0f));
    glm::mat4 atmosPosition = glm::translate(I, glm::vec3(0.0f, -earthRadius - 1000.0f, 0.0f));

    planet = new Sphere(earthRadius, earthPosition);
    atmosphere = new Sphere(atmosphereRadius, atmosPosition);
}


// Changes made from original script:
// Camera is currently closer to the origin rather than having the atmosphere and earth at (0,0)
// We don't have a near or far intersection (t0, t1) -> (tmin, tmax), only the closest intersection is returned. This is fine as long as we are inside the atmosphere
// We also made atmosphere return a reference, otherwise it  was being overwritten by a triangle????
// 

glm::vec3 Atmosphere::computeIncidentLight(Ray ray, float tmin, float tmax) const
{
    Point pt = atmosphere->Intersect(ray);
    float t1 = pt.GetDistance();
    if (t1 == INFINITY)
    {
        // TODO: implement lighting from outside of the atmosphere. Basically, the sphere intersection needs to return both points of intersection, not just the larger one

        return glm::vec3(0.0f);
    }

    // We bind the maximum length to the intersection pt in the atmosphere
    tmax = t1;

    // TODO: try from the inside of a sphere

    glm::vec3 rayDir = ray.GetDirection();
    glm::vec3 originPos = ray.GetPosition();

    uint32_t numSamples = 16;
    uint32_t numSamplesLight = 8;
    float segmentLength = (tmax - tmin) / numSamples;
    float tCurrent = tmin;
    glm::vec3 sumR(0.0f), sumM(0.0f);  // mie and rayleigh contribution 
    float opticalDepthR = 0.0f, opticalDepthM = 0.0f;
    float mu = dot(ray.GetDirection(), sunDirection);  // mu in the paper which is the cosine of the angle between the sun direction and the ray direction 
    float phaseR = 3.f / (16.f * glm::pi<float>() * (1.0f + mu * mu));
    float g = 0.76f;
    float phaseM = 3.f / (8.f * glm::pi<float>()) * ((1.f - g * g) * (1.f + mu * mu)) / ((2.f + g * g) * pow(1.f + g * g - 2.f * g * mu, 1.5f));

    for (uint32_t i = 0; i < numSamples; ++i) {
        glm::vec3 samplePosition = originPos + (tCurrent + segmentLength * 0.5f) * rayDir;
        float height = glm::length(samplePosition - planet->GetPosition()) - earthRadius;

        // compute optical depth for light
        float hr = exp(-height / Hr) * segmentLength;
        float hm = exp(-height / Hm) * segmentLength;
        opticalDepthR += hr;
        opticalDepthM += hm;
        
        Ray sampleDir(samplePosition, sunDirection);
        Point pt = atmosphere->Intersect(sampleDir);

        // NOTE: the reference implementation uses the 'farther' intersection of the sphere 
        float segmentLengthLight = pt.GetDistance() / numSamplesLight, tCurrentLight = 0.0f;
        float opticalDepthLightR = 0.0f, opticalDepthLightM = 0.0f;
        uint32_t j = 0;

        for (j = 0; j < numSamplesLight; ++j) {
            glm::vec3 samplePositionLight = samplePosition + (tCurrentLight + segmentLengthLight * 0.5f) * sunDirection;
            float heightLight = glm::length(samplePositionLight - planet->GetPosition()) - earthRadius;
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
    return (sumR * betaR * phaseR + sumM * betaM * phaseM) * 200000.0f; 
}
