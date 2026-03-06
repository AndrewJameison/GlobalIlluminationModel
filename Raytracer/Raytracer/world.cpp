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

void World::Add(Object* obj)
{
    objects.push_back(obj);
}

void World::Add(Light light)
{
    lights.push_back(light);
}

glm::vec3 World::Spawn(Ray ray)
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
        
        return model->Illuminate(intersection, object);
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
        return atmosphere->computeIncidentLight(ray, 0.0f, w);
        //return glm::vec3(0.0f);
    }

}

