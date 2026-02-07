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
        float dist = obj->Intersect(ray);

        // TODO: Add a distance check to the if statment to find closest intersection
        if (dist != INFINITY && dist < w)
        {
            w = dist;
            intersection = obj;
        }
    }
    
    // Return the resulting color value of the ray's journey
    if (intersection != nullptr)
    {
        // For now, just return a basic color for each object. In future, have proper shading
        //if (typeid(*intersection) == typeid(Sphere))
        //return intersection->color;
        return sf::Color::Green;
    }
    
    else
    {
        return backgroundColor;
    }
}

