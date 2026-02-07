#include "world.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

World::World(sf::Color bgColor)
{
    backgroundColor = bgColor;

    objects = std::vector<Object*>();
}

World::~World()
{
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

sf::Color World::Spawn(Ray ray)
{
    float w = INFINITY;
    Object* intersection = nullptr;
    
    // For each object in the world check for intersection with the ray
    for (Object* obj : objects)
    {
        Point point = obj->Intersect(ray);

        if (point.GetDistance() < w)
        {
            w = point.GetDistance();
            intersection = obj;
        }
    }
    
    // Return the resulting color value of the ray's journey
    if (intersection != nullptr)
    {
        return intersection->color;
    }
    
    else
    {
        return backgroundColor;
    }
}

