#pragma once
#include "world.hpp"
#include <glm/ext/matrix_transform.hpp>

#define uint unsigned int

const uint imageWidth = 800;
const uint imageHeight = 600;
const float maxIValue = 1.0f;
const float EPSILON = 0.000001f;

const glm::vec3 Illuminace_CRT = glm::vec3(0.27f, 0.67f, 0.06f);

typedef glm::vec4 filmPlaneBuffer[imageHeight];


// NOTE: All tone reproduction operators should return a scale factor to be applied to the color values

class Camera {
public:
    void LookAt(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 upVector);
    void Render(World world);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="luminanceMax"></param>
    /// <param name="adaptaionLuminance"></param>
    /// <returns>Color correction scale factor</returns>
    float WardTR(float luminanceMax, float adaptaionLuminance);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="a"></param>
    /// <param name="keyValue"></param>
    /// <param name="maxLuminanceDisplay"></param>
    /// <param name="worldLuminance"></param>
    /// <returns>Color correction scale factor</returns>
    float ReinhardTR(float a, float keyValue, float maxLuminanceDisplay, float worldLuminance);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="bias"></param>
    /// <param name="adaptaionLuminance"></param>
    /// <param name="maxLuminanceDisplay"></param>
    /// <param name="worldLuminance"></param>
    /// <returns>Color correction scale factor</returns>
    float AdaptiveLogTR(float bias, float adaptaionLuminance, float maxLuminanceDisplay, float worldLuminance);

    double LogAverageLuminance();

    Camera(float focalLen, float fov, glm::vec3 pos);
    ~Camera();

private:
    float focalLength; // Length between camera and the film plane

    // Camera Coordinates
    float filmPlaneWidth;
    float filmPlaneHeight;

    /// <summary>
    /// Data stored on the film plane in the format of [r,g,b, illuminance]
    /// </summary>
    filmPlaneBuffer* buffer;

    glm::vec3 position;
    glm::mat4 viewMatrix; // moves coords from camera space to world space
};
