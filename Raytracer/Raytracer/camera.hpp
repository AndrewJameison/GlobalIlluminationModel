#pragma once
#include "world.hpp"

class Camera {
  public:
    void LookAt(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 upVector);
    void Render(World world);
    Camera(float focalLen, unsigned int im_x, unsigned int im_y, float fov, glm::vec3 pos);

  private:
    float focalLength; // Length between camera and the film plane

    // Discrete pixel coordinates
    unsigned int imageWidth;
    unsigned int imageHeight;
    
    // Camera Coordinates
    float filmPlaneWidth;
    float filmPlaneHeight;
    
    glm::vec3 position;
    glm::mat4 viewMatrix; // moves coords from world space to camera space

};
