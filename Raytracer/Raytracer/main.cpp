#include <iostream>
#include <stdio.h>
#include "camera.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "phong.hpp"

// Written by Andrew Jameison for Joe Geigel's Global Illumination course CSCI 711.01
// This program uses SFML 2.6 for displaying the image to the screen
// This program uses LHS order to handle vector and matrix math
    // pos. rotation is clockwise, and pos-z goes into the screen
    // Row major order for matrices pre multiply matrices M = OLD * NEW 

// ----------------------- Objects -----------------------
// Sphere 1
const float S1_RADIUS = 3.0f;
const glm::vec3 S1_ORIGIN = glm::vec3(-5.0f, 4.0f, -0.15f);
// Sphere 2
const float S2_RADIUS = 3.0f;
const glm::vec3 S2_ORIGIN = glm::vec3(-3.0f, 3.0f, 1.2f);

// Platform
const glm::vec3 v0 = glm::vec3(-10.0f, 0.0f, -50.0f);
const glm::vec3 v1 = glm::vec3(10.0f, 0.0f, -50.0f);
const glm::vec3 v2 = glm::vec3(10.0f, 0.0f, 50.0f);
const glm::vec3 v3 = glm::vec3(-10.0f, 0.0f, 50.0f);

// ----------------------- Lighting -----------------------
// Light 1
const glm::vec3 L1_LIGHT_POS = glm::vec3(-5.0f, 14.0f, -4.0f);
const glm::vec3 L1_IRRADIANCE = glm::vec3(1.0f, 1.0f, 1.0f);
// Light 2
const glm::vec3 L2_LIGHT_POS = glm::vec3(-2.0f, 10.0f, -4.0f);
const glm::vec3 L2_IRRADIANCE = glm::vec3(1.0f, 1.0f, 1.0f);

// ---------------------- World Units ----------------------
// Camera values
const float FOCAL_LENGTH = 1.0f;
const float FOV = 100.0f;

const glm::vec3 CAM_ORIGIN = glm::vec3(-5.0f, 3.0f, -5.0f);
const glm::vec3 CAM_TARGET = glm::vec3(-5.0f, 3.0f, 6.0f);
const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
    // NOTE: Any objects have to be created using pointers because of the abstract base Object class
    Phong* lightModel = new Phong();
    World world = World(lightModel);
    
    // TODO: make the extra credit LAST, have pictures of each stage of the project
        // TODO: Multiple lighting (1pt)
        // TODO: Second Illumination model (1pt)
        // TODO: Super sampling (1pt)

    // TODO: puts lights back on the heap? Looping through them in camera is expensive apparently.
    world.Add(Light(L1_LIGHT_POS, L1_IRRADIANCE));
    world.Add(Light(L2_LIGHT_POS, L2_IRRADIANCE));

    // Create and add objects to the world
    world.Add(new Sphere(S1_RADIUS, S1_ORIGIN));
    world.Add(new Sphere(S2_RADIUS, S2_ORIGIN));

    world.Add(new Triangle(v0, v1, v2));
    world.Add(new Triangle(v2, v3, v0));
    
    // Setup Camera
    Camera camera = Camera(FOCAL_LENGTH, FOV, CAM_ORIGIN);
    camera.LookAt(CAM_ORIGIN, CAM_TARGET, WORLD_UP);
    camera.Render(world);

    return 0;
}