#include "world.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

World::World(Illumination* lightModel)
{
    model = lightModel;
    objects = std::vector<Object*>();
    lights = std::vector<Light*>();
}

World::~World()
{
    delete model;

    for (Object* obj : objects)
    {
        delete obj;
    }
    for (Light* light : lights)
    {
        delete light;
    }

    objects.clear();
    lights.clear();
}

void World::Add(Object* obj)
{
    objects.push_back(obj);
}

void World::Add(Light* light)
{
    lights.push_back(light);
}

glm::vec3 World::Spawn(Ray ray)
{
    // TODO: get rid of w, the intersection
    float w = INFINITY;
    Point intersection = Point(INFINITY, glm::vec3(), glm::vec3(), glm::vec3());// , nullptr);
    
    // For each object in the world check for intersection with the ray
    for (Object* obj : objects)
    {
        Point point = obj->Intersect(ray);

        if (point.GetDistance() < w)
        {
            w = point.GetDistance();
            intersection = point;
        }
    }
    
    // Return the resulting color value of the ray's journey
    if (w != INFINITY)
    {
        // TODO: pass the point into an illuminance model, return an irradiance value
        for (Light* light : lights)
        {
            // Cast a shadow ray to the light source
            bool isClear = true;
            Ray shadowRay(intersection.GetPosition(), light->GetPosition());

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
    }

    return model->Illuminate(intersection);
}

