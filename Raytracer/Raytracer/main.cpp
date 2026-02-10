#include <iostream>
#include <stdio.h>
#include "camera.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"

// Written by Andrew Jameison for Joe Geigel's Global Illumination course CSCI 711.01
// This program uses SFML 2.6 for displaying the image to the screen
// This program uses LHS order to handle vector and matrix math
    // pos. rotation is clockwise, and pos-z goes into the screen
    // Row major order for matrices pre multiply matrices M = OLD * NEW 

// TODO: Write some global variables, uint, etc. 

#define uint unsigned int

// Object Values
// Sphere 1
const float S1_RADIUS = 3.0f;
const glm::vec3 S1_ORIGIN = glm::vec3(-5.0f, 4.0f, -0.15f);
// Sphere 2
const float S2_RADIUS = 3.0f;
const glm::vec3 S2_ORIGIN = glm::vec3(-3.0f, 3.0f, 2.2f);

// Platform
const glm::vec3 PLANE_ORIGIN = glm::vec3(0.0f);
const glm::vec3 PLANE_SCALE = glm::vec3(20.0f, 1.0f, 100.0f);
const glm::vec3 ZERO = glm::vec3(0.0f);

const glm::vec3 v0 = glm::vec3(-10.0f, 0.0f, -50.0f);
const glm::vec3 v1 = glm::vec3(10.0f, 0.0f, -50.0f);
const glm::vec3 v2 = glm::vec3(10.0f, 0.0f, 50.0f);
const glm::vec3 v3 = glm::vec3(-10.0f, 0.0f, 50.0f);

// Camera Variables

// Camera Coordinates (pixels)
const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = 600;

// World Units
const float FOCAL_LENGTH = 1.0f;
const float FOV = 100.0f;

const glm::vec3 CAM_ORIGIN = glm::vec3(10.0f, 3.0f, 7.0f);
const glm::vec3 CAM_TARGET = glm::vec3(-5.0f, 3.0f, 6.0f);
const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
    World world = World();
    
    // Create and add objects to the world
    Sphere* s1 = new Sphere(S1_RADIUS, S1_ORIGIN, sf::Color::Blue);
    Sphere* s2 = new Sphere(S2_RADIUS, S2_ORIGIN, sf::Color::Cyan);

    Triangle* t1 = new Triangle(v0, v1, v2, sf::Color::Red);
    Triangle* t2 = new Triangle(v2, v3, v0, sf::Color::Red);

    world.Add(s1);
    world.Add(s2);

    world.Add(t1);
    world.Add(t2);
    
    // Setup Camera
    Camera camera = Camera(FOCAL_LENGTH, IMAGE_WIDTH, IMAGE_HEIGHT, FOV, CAM_ORIGIN);
    camera.LookAt(CAM_ORIGIN, S2_ORIGIN, WORLD_UP);
    camera.Render(world);

    return 0;
}