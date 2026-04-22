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

Ray World::Reflection(Ray ray, Point intersection)
{
    glm::vec3 N = intersection.GetNormal();
    glm::vec3 I = ray.GetDirection();

    glm::vec3 reflection = I - 2.0f * (glm::dot(I, N)) * N;

    // Offset the origin of the reflection by just a little bit to prevent intersection with self
    glm::vec3 pos = intersection.GetPosition() + reflection * 0.01f;

    return Ray(pos, pos + reflection);
}

Ray World::Transmission(float nt, Ray ray, Point intersection)
{
    // QUESTION: Does D refer to the direction vector of the incoming ray?    
    glm::vec3 N = intersection.GetNormal();
    glm::vec3 I = ray.GetDirection();
    glm::vec3 transmissive = I;
    float ni = AIR_INDEX_REFRACTION;

    // Quickly check to see if the indices of refraction are the same, no need to bend light if so
    if (ni != nt)
    {
        // Determine whether we are inside or outside of the object
        if (glm::dot(N, I) >= 0.0f)
        {
            N *= -1.0f;
        
            // Swap the refractive indices of the materials if we are inside
            float t = ni;
            ni = nt;
            nt = t;
        }

        // calculate the direction of the reflective ray
        float nRatio = ni / nt;
        float cos = glm::dot(-I, N);
        float sin2 = glm::pow(nRatio, 2.0f) * (1.0f - glm::pow(cos, 2.0f));

        // Check for total internal reflection
        // QUESTION: why do we compare sin2 to this value? What is the practical significance?
        if (sin2 > 1.0f)
        {
            transmissive = I - 2 * dot(I, N) * N;
        }
        else
        {
            transmissive = nRatio * I + (nRatio * cos - glm::sqrt(1 - sin2)) * N;
        }
    }
        
    // Deal with proper shadow rays (EXTRA)

    // Offset the origin of the transmission by just a little bit to prevent intersection with self
    glm::vec3 pos = intersection.GetPosition() + transmissive * 0.01f;
    return Ray(pos, pos + transmissive);
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
        float transmissionValue = 1.0f;

        // Cast out the shadow rays
        for (const Light& light : lights)
        {
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
                    float kt = obj->GetMaterial()->GetTransmission();

                    // Pseudo solve for shadow rays hitting transparent objects
                    if (kt > 0.0f)
                    {
                        transmissionValue *= kt;
                    }

                    else 
                    {
                        isClear = false;
                        break;
                    }
                }
            }

            // If there were never any objects to block the way, add this light and its direction
            if (isClear)
            {
                intersection.AddLight(light, shadowRay.GetDirection());
            }
        }

        // Local Illumination
        glm::vec3 retcolor = transmissionValue * model->Illuminate(intersection, object);

        // Recursively look for transmittance and reflection
        // TODO: The mix between reflectance and transmission looks pretty noticable, blend it somehow?
        if (depth < MAX_DEPTH)
        {
            float kr = object->GetMaterial()->GetReflection();
            float kt = object->GetMaterial()->GetTransmission();

            if (kr > 0.0f)
            {
                retcolor += kr * Spawn(depth + 1, Reflection(ray, intersection));
            }

            if (kt > 0.0f)
            {                
                retcolor += kt * Spawn(depth + 1, Transmission(kt, ray, intersection));
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

