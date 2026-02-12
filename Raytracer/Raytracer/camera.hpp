#pragma once
#include "world.hpp"

#define uint unsigned int


const uint imageWidth = 800;
const uint imageHeight = 600;
const float maxIValue = 1.0f;

typedef glm::vec3 filmPlaneBuffer[imageWidth];

class Camera {
    public:
        void LookAt(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 upVector);
        void Render(World world);
        Camera(float focalLen, float fov, glm::vec3 pos);
        ~Camera();

    private:
        float focalLength; // Length between camera and the film plane
    
        // Camera Coordinates
        float filmPlaneWidth;
        float filmPlaneHeight;

        //glm::vec3* filmPlaneBuffer;
        filmPlaneBuffer* buffer;
    
        glm::vec3 position;
        glm::mat4 viewMatrix; // moves coords from world space to camera space

};
