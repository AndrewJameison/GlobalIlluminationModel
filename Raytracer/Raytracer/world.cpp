#include "world.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

World::World(Illumination* lightModel)
{
    model = lightModel;
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
// for (Light* light : lights)
// {
//     delete light;
// }

    objects.clear();
    //lights.clear();
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
    if (object != nullptr)
    {
        for (Light light : lights)
        {
            // Cast a shadow ray to the light source
            bool isClear = true;

            glm::vec3 temp = glm::normalize(light.GetPosition() - intersection.GetPosition()) * 0.01f;

            Ray shadowRay(intersection.GetPosition() + temp, light.GetPosition());

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

    return model->Illuminate(intersection, object);
}

