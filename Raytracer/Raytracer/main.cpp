#include <iostream>
#include <stdio.h>
#include "camera.hpp"
#include "mesh.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "phong.hpp"
#include "phong-blinn.hpp"
#include "m_checker.hpp"
#include "m_brick.hpp"

// Written by Andrew Jameison for Joe Geigel's Global Illumination course CSCI 711.01
// This program uses SFML 2.6 for displaying the image to the screen
// This program uses LHS order to handle vector and matrix math
    // pos. rotation is clockwise, and pos-z goes into the screen
    // Row major order for matrices pre multiply matrices M = OLD * NEW

const glm::mat4 I = glm::mat4(1.0f);

// ----------------------- Objects -----------------------
// Sphere 1
const float S1_RADIUS = 2.0f;
const glm::mat4 S1_MODEL_T = glm::translate(I, glm::vec3(-5.0f, 4.0f, -1.2f));

// Sphere 2
const float S2_RADIUS = 2.0f;
const glm::mat4 S2_MODEL_T = glm::translate(I, glm::vec3(-1.8f, 3.0f, 1.2f));

// Platform
const glm::vec3 v0 = glm::vec3(-10.0f, 0.0f, -20.0f);
const glm::vec3 v1 = glm::vec3(10.0f, 0.0f, -20.0f);
const glm::vec3 v2 = glm::vec3(10.0f, 0.0f, 20.0f);
const glm::vec3 v3 = glm::vec3(-10.0f, 0.0f, 20.0f);

// Plane
const glm::vec3 PLANE_NORMAL = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::mat4 PLANE_MODEL_T = glm::translate(I, glm::vec3(0.0f));


// ----------------------- Material -----------------------
Material* m_checkers = new CheckersMaterial(0.0f, 0.0f, 0.25f);
Material* m_brick = new BrickMaterial(0.0f, 0.0f, 1.0f, 0.45f, 0.1f);
Material* m_reflective = new PhongMaterial(0.8f, 0.0f, glm::vec3(0.0f));
Material* m_transmissive = new PhongMaterial(0.0f, 0.55f, glm::vec3(0.0f));


// ----------------------- Meshes -----------------------

// ----------------------- Lighting -----------------------
// The Sun
const float SUN_IRRADIANCE = 200000.0f;
const float SUN_ROTATION = 0.0f;
const glm::vec3 SUN_ROT_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);

// Light 1
const glm::vec3 L1_LIGHT_POS = glm::vec3(-5.0f, 6.0f, -4.0f);
const glm::vec3 L1_IRRADIANCE = glm::vec3(100.0f, 100.0f, 100.0f);
// Light 2
const glm::vec3 L2_LIGHT_POS = glm::vec3(-8.0f, 10.0f, -4.0f);
const glm::vec3 L2_IRRADIANCE = glm::vec3(100.0f, 100.0f, 100.0f);


// ---------------------- World Units ----------------------
// Camera values
const float FOCAL_LENGTH = 1.0f;
const float FOV = 100.0f;

const glm::vec3 CAM_ORIGIN = glm::vec3(-5.0f, 3.5f, -5.0f);
const glm::vec3 CAM_TARGET = glm::vec3(-5.0f, 3.5f, 6.0f);
const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
    // TODO: read in object data using assimp
	// TODO: measure the runtime of rendering with and without a KD tree
    // TODO: replace the objects list in world.cpp with a KD tree, adding should add to this tree
    // TODO: render in world.cpp should navigate the KD tree for each ray. Use TA-B traversal for coordinate checking

    // EXTRA: SAH partitioning, instead of simply splitting subdivisions in half

    // NOTE: Any objects have to be created using pointers because of the abstract base Object class
	PhongBlinn* lightModel = new PhongBlinn();
    Atmosphere* atmosphere = new Atmosphere(SUN_IRRADIANCE, SUN_ROTATION, SUN_ROT_AXIS);
    World world = World(lightModel, atmosphere);
    //Mesh* pMesh = new Mesh();

    world.Add(Light(L1_LIGHT_POS, L1_IRRADIANCE));
    world.Add(Light(L2_LIGHT_POS, L2_IRRADIANCE));

    // Create and add objects to the world
    world.Add(new Sphere(S1_RADIUS, S1_MODEL_T, m_transmissive));
    world.Add(new Sphere(S2_RADIUS, S2_MODEL_T, m_reflective));

    world.Add(new Triangle(v2, v1, v0, m_checkers));
    world.Add(new Triangle(v0, v3, v2, m_checkers));
	//world.Add(new Plane(PLANE_NORMAL, PLANE_MODEL_T, checkers));

    //pMesh->Render(world);
    
    // Setup Camera
    Camera camera = Camera(FOCAL_LENGTH, FOV, CAM_ORIGIN);
    camera.LookAt(CAM_ORIGIN, CAM_TARGET, WORLD_UP);
    camera.Render(world);

    return 0;
}