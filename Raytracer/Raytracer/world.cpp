#include "world.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

World::World(sf::Color amb)
{
    ambientColor = amb;
    objects = std::vector<Object*>();
    lights = std::vector<Light*>();
}

World::~World()
{
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

glm::vec3 World::Spawn(Ray ray)
{
    float w = INFINITY;
    Point intersection;
    
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
        // TODO: Create a basic illumination model class
        // TODO: Calculate the shadow vector to every light in the scene here?
        // TODO: create a Phong child class of the model
        // TODO: create a phong Blinn child class of the model (1pt)

        // TODO: pass the point into an illuminance model, return an irradiance value
            // pass along the lights vector
            // pass along incoming and reflective???

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

        //return intersection->color;
    }
    
    // TOOD: move nullptr check to illumination model, instead just pass along the intersection ptr and return the irradiance value
    else
    {
        // Background Ambient irradiance value, will be replaced in week 13
        // TODO: rename variable to ambient value
        return ambientColor;
    }
}

