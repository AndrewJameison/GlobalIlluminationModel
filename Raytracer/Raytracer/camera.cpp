#include <SFML/graphics.hpp>
#include "SFML/System.hpp"
#include <iostream>
#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(float focalLen, float fov, glm::vec3 pos)
{
    focalLength = focalLen;
    position = pos;

    viewMatrix = glm::mat4(1.0f);

    filmPlaneHeight = 2.0f * glm::tan((fov * glm::pi<float>() / 180.0f) / 2.0f) * focalLen;
    float ratio = (float)imageWidth / (float)imageHeight;
    filmPlaneWidth = ratio * filmPlaneHeight;

    buffer = new filmPlaneBuffer[imageWidth];
}

Camera::~Camera()
{
    delete[] buffer;
}

void Camera::Render(World world)
{
    // Create our window, put an image on a texture and assign it to the sprite, that sprite is our camera view
    sf::Vector2u imageSize = sf::Vector2u(imageWidth, imageHeight);
    sf::RenderWindow window(sf::VideoMode(imageSize), "Raytracer works!");
    sf::Image image(imageSize, sf::Color::White);
    sf::Texture texture;
    
    // Pseudo rotated grid pattern values for supersampling
    // TODO: Add a supersampling option (toggle) and number of samples (rays) to apply for each pixel, then average them
        // NOTE: This is a really good place for a further project. Wait until I have more time to work on this
        // NOTE: To improve performance with anti-aliasing, add a "pre sampling" step to the antialiasing for edges and the like
        // NOTE: Another performance improvement is to take a few "test" samples to gauge similarity, then proceed with the rest if sufficently different
    const glm::vec3 sampleOff[4] = { 
        glm::vec3(0.1f, 0.4f, 0.0f), 
        glm::vec3(0.4f, -0.1f, 0.0f), 
        glm::vec3(-0.1f, -0.4f, 0.0f), 
        glm::vec3(-0.4f, 0.1f, 0.0f) 
    };

    if (auto _ = !texture.loadFromImage(image))
        printf("ERROR: unable to load texture from image\n");

    sf::Sprite sprite(texture);

    float toneMax = 0.0f;

    // Size of each pixel in camera coordinates
    float pxWidth = filmPlaneWidth / float(imageWidth);
    float pxHeight = filmPlaneHeight / float(imageHeight);

    // Define dimensions in camera space
    glm::vec4 pxCamera = glm::vec4(-filmPlaneWidth / 2.0f + pxWidth / 2.0f,
        filmPlaneHeight / 2.0f - pxHeight / 2.0f,
        focalLength, 1.0f);

    // convert camera coordinates to world space
    glm::vec4 pxWorld = viewMatrix * pxCamera;
    glm::vec3 p1 = glm::vec3(pxWorld) / pxWorld.w;

    // convert increment values to world space
    glm::vec4 xWorld = viewMatrix * (pxCamera + glm::vec4(pxWidth, 0.0f, 0.0f, 0.0f));
    glm::vec4 yWorld = viewMatrix * (pxCamera + glm::vec4(0.0f, -pxHeight, 0.0f, 0.0f));

    // NOTE: we add the pixel dimensions of the camera space...
    // ...and then subtract the pixel dimensions of the world space to center the increment values at the world origin
    glm::vec3 dx = (glm::vec3(xWorld) / xWorld.w) - p1;
    glm::vec3 dy = (glm::vec3(yWorld) / yWorld.w) - p1;

    // For each pixel on the film plane, spawn a ray in with world coordinates
    for (uint v = 0; v < imageHeight; v++)
    {
        for (uint u = 0; u < imageWidth; u++)
        {
            glm::vec3 sample = glm::vec3(0.0f);

            // Post supersampling of the pixel space using a pseudo rotated grid pattern
            // TODO: replace with a vector of samples based on a samples parameter
            for (uint i = 0; i < 4; i++)
            {
                glm::vec3 target_pixel = p1 + float(u) * dx + float(v) * dy;
				target_pixel.x += sampleOff[i].x * pxWidth;
				target_pixel.y += sampleOff[i].y * pxHeight;
                sample += world.Spawn(Ray(position, target_pixel));
            }

            float toneSample = glm::max(glm::max(sample.x, sample.y), sample.z);

            if (toneSample > toneMax)
            {
                toneMax = toneSample;
            }

            buffer[u][v] = sample;
        }
    }

    // Tone Reproduction
    for (uint v = 0; v < imageHeight; v++)
    {
        for (uint u = 0; u < imageWidth; u++)
        {
            glm::vec3 irradiance = buffer[u][v] / toneMax;

            uint r = (uint)(irradiance.x * 255.0f);
            uint g = (uint)(irradiance.y * 255.0f);
            uint b = (uint)(irradiance.z * 255.0f);

            image.setPixel(sf::Vector2u(u, v), sf::Color(r, g, b));
        }
    }

    // Keeping the window open
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // NOTE: We are assuming that the image is referencing the texture directly, not by copy
        texture.update(image);
        window.draw(sprite);
        window.display();
    }
}

void Camera::LookAt(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 upVector)
{   
    // We move from camera space to world space, so our viewMatrix goes in reverse
    viewMatrix = glm::inverse(glm::lookAtLH(cameraPosition, targetPosition, upVector));
    position = cameraPosition;
 }
