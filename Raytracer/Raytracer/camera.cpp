#include <SFML/graphics.hpp>
#include "SFML/System.hpp"
#include <iostream>
#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(float focalLen, unsigned int im_x, unsigned int im_y, float fov, glm::vec3 pos)
{
    viewMatrix = glm::mat4(1.0f);

    focalLength = focalLen;

    imageWidth = im_x;
    imageHeight = im_y;

    filmPlaneHeight = 2.0f * glm::tan((fov * glm::pi<float>() / 180.0f) / 2.0f) * focalLen;
    float ratio = (float)im_x / (float)im_y;
    filmPlaneWidth = ratio * filmPlaneHeight;

    position = pos;
}

void Camera::Render(World world)
{
    // Create our window, put an image on a texture and assign it to the sprite, that sprite is our camera view
    sf::Vector2u imageSize = sf::Vector2u(imageWidth, imageHeight);
    sf::RenderWindow window(sf::VideoMode(imageSize), "Raytracer works!");
    sf::Image image(imageSize, sf::Color::White);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    
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

        // Size of each pixel in camera coordinates
        float pxWidth  = filmPlaneWidth  / float(imageWidth);
        float pxHeight = filmPlaneHeight / float(imageHeight);

        // Define dimensions in camera space
        glm::vec4 pxCamera= glm::vec4(-filmPlaneWidth/2.0f + pxWidth/2.0f,
                                    filmPlaneHeight/2.0f - pxHeight/2.0f,
                                    focalLength, 1.0f);
                                    
        // convert camera coordinates to world space
        // TODO: move transpose and inverse into lookat? if it never changes, why calc. every frame?
        glm::mat4 invView = glm::inverse(viewMatrix);
        glm::vec4 pxWorld = invView * pxCamera;
        glm::vec3 p1 = glm::vec3(pxWorld) / pxWorld.w;

        // convert increment values to world space
        glm::vec4 xWorld = invView * (pxCamera + glm::vec4(pxWidth, 0.0f, 0.0f, 0.0f));
        glm::vec4 yWorld = invView * (pxCamera + glm::vec4(0.0f, -pxHeight, 0.0f, 0.0f));

        // NOTE: we add the pixel dimensions of the camera space...
        // ...and then subtract the pixel dimensions of the world space to center the increment values at the world origin
        glm::vec3 dx = (glm::vec3(xWorld) / xWorld.w) - p1;
        glm::vec3 dy = (glm::vec3(yWorld) / yWorld.w) - p1;
        
        // For each pixel on the film plane, spawn a ray in with world coordinates
        for (unsigned int v = 0; v < imageHeight; v++)
        {
            for (unsigned int u = 0; u < imageWidth; u++)
            {
                glm::vec3 target_pixel = p1 + float(u) * dx + float(v) * dy;

                Ray ray(position, target_pixel);
                sf::Color color = world.Spawn(ray);
                image.setPixel(sf::Vector2u(u, v), color);
            }
        }
        
        // NOTE: We are assuming that the image is referencing the texture directly, not by copy
        texture.update(image);
        window.draw(sprite);
                
        window.display();
    }
}

void Camera::LookAt(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 upVector)
{   
    viewMatrix = glm::lookAtLH(cameraPosition, targetPosition, upVector);
    position = cameraPosition;
 }
