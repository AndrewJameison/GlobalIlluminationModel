#include "world.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

World::World(Illumination* lightModel, Atmosphere* atmo)
{
    model = lightModel;
    atmosphere = atmo;
    objects = std::vector<Object*>();
    lights = std::vector<Light>();
}

World::~World()
{
    delete model;

    for (Object* obj : objects)
    {
        delete obj;
    }

    objects.clear();
}

glm::vec3 World::PerfectReflection(int depth, float kr, Ray ray, Point intersection)
{
    glm::vec3 N = intersection.GetNormal();
    glm::vec3 I = ray.GetDirection();

    glm::vec3 reflection = I - 2.0f * (glm::dot(I, N)) * N;

    // Offset the origin of the reflection by just a little bit to prevent intersection with self
    glm::vec3 pos = intersection.GetPosition() + reflection * 0.01f;

    return kr * Spawn(depth, Ray(pos, pos + reflection));
}

glm::vec3 World::MonteCarloReflection(int depth, int samples, float kr, Point intersection)
{
    //TODO: get rid of ambient value, its screwing with the color situation

    glm::vec3 retcolor = glm::vec3();

    for (int i = 0; i < samples; i++)
    {
        retcolor += Spawn(depth, model->ReflectionEquation(intersection));
    }

    return kr * retcolor / (float)samples;
}

void World::Add(Object* obj)
{
    objects.push_back(obj);
}

void World::Add(Light light)
{
    lights.push_back(light);
}

glm::vec3 World::Spawn(int depth, Ray ray)
{
    Point intersection = Point();
    Object* object = nullptr;
    
    // For each object in the world check for intersection with the ray
    for (Object* obj : objects)
    {
        Point point = obj->Intersect(ray);

        if (point.GetDistance() < intersection.GetDistance())
        {
            intersection = point;
            object = obj;
        }
    }
    
    // Return the resulting color value of the ray's journey
    if (object)
    {
        for (const Light& light : lights)
        {
            // Cast a shadow ray to the light source
            bool isClear = true;

            // Create a small offset to prevent intersection the object itself
            glm::vec3 offset = glm::normalize(light.GetPosition() - intersection.GetPosition()) * 0.01f;

            Ray shadowRay(intersection.GetPosition() + offset, light.GetPosition());

            for (Object* obj : objects)
            {
                Point point = obj->Intersect(shadowRay);

                // If we ever intersect with an object, move on to the next light
                if (point.GetDistance() != INFINITY)
                {
                    isClear = false;
                    break;
                }
            }

            // If there were never any objects to block the way, add this light and its direction
            if (isClear)
            {
                intersection.AddLight(light, shadowRay.GetDirection());
            }
        }

        glm::vec3 retcolor = model->Illuminate(intersection, object);

        // Recursively look for transmittance and reflection
        if (depth < MAX_DEPTH)
        {
            float kr = object->GetMaterial()->GetReflection();
            float kt = object->GetMaterial()->GetTransmission();

            if (kr > 0.0f)
            {
                // Create a small offset to prevent intersection the object itself
                retcolor += PerfectReflection(depth + 1, kr, ray, intersection);
            }

            // TODO: add transmission assn 6
            if (kt > 0.0f)
            {
                // Do a flip!

                // TODO: spawn transmission ray; 
                // TODO: retcolor += kt * Spawn(depth + 1, transmission ray)
            }
        }
        
        return retcolor;
    }

    // We use atmospheric lighting
    else
    {
        // Does the ray intersect the planetory body? (the intersection test is against the Earth here
        // not against the atmosphere). If the ray intersects the Earth body, we pass that value into w.
        // If the viewing ray doesn't hit the Earth, or course, the ray
        // is then bounded to the range [0:INF]. In the method computeIncidentLight() we then
        // compute where this primary ray intersects the atmosphere, and we limit the max t range 
        // of the ray to the point where it leaves the atmosphere.
        float w = atmosphere->IntersectPlanet(ray).GetDistance();

        // The *viewing or camera ray* is bounded to the range [0:w]
        //return atmosphere->computeIncidentLight(ray, 0.0f, w);
        return BACKGROUND_COLOR;
    }

}

