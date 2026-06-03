#include "m_tile.hpp"

// A quick helper function to deal with tricky fMod calculations when negative
float properFMod(float value, float maxValue)
{
    float f = fmod(value, maxValue);

    if (f < 0.0f) f += maxValue;

    return f;
}

glm::vec3 TileMaterial::GetDiffuse(glm::vec2 uv)
{
    int w = grid.size();
    float gridWidth = tile_width + 2.0f * grout_width;
    float patternWidth = w * gridWidth;

    // Wrap the projected space of the whole texture
    float u = properFMod(uv.x, patternWidth);
    float v = properFMod(uv.y, patternWidth);

    // Check to see if we are in a grout area by 'wrapping' a grid space
    float g = properFMod(uv.x, gridWidth);
    float r = properFMod(uv.y, gridWidth);

    // Move to grid space to check color value
    u /= gridWidth;
    v /= gridWidth;

    int uu = int(std::floor(u));
    int vv = int(std::floor(v));

    // Check if we are near any edges of the grid space, store it's cardinal grid direction if we are
    int gg = 0;
    int rr = 0;

    if (g <= grout_width) gg = -1;
    else if (g > grout_width + tile_width) gg = 1;

    if (r <= grout_width) rr = -1;
    else if (r > grout_width + tile_width) rr = 1;

    // If we do have a neighbor, compare it to our tile
    if (gg || rr)
    {
        gg = (uu + gg) % w;
        rr = (vv + rr) % w;

        if (gg < 0) gg += w;
        if (rr < 0) rr += w;
        
        // If the neighboring tile is NOT the same type of tile, we've reached some grout
        if (grid[gg][rr] != grid[uu][vv])
        {
            return grout_color;
        }
    }

    // Only for the tiles, we introduce some noisy discoloration
    glm::vec3 baseColor;

    switch (grid[uu][vv])
    {
        case Slab1:
        case Slab2:
        case Slab3:
        case Slab4:
        case Square2:
        case Vert4:
            baseColor = color_option_2;
            break;

        default:
            baseColor = color_option_1;
            break;
    }

    // A few layers of brownian noise adds to the dirty texture of the tile - but it could be better...
    // Need more root-like darker lines mixed into the softer grey / white noise
    double tileOffset = noise.unsignedRawNoise(uu * 0.1, vv * 0.1);

    double n = noise.unsignedFBM(
        g + tileOffset * 10.0,
        r + tileOffset * 10.0,
        octaves,
        lacunarity,
        gain
    );

    float noiseCutoff = 0.85f;
    float noiseWeight = 0.55f;

    return (n < noiseCutoff) ? glm::mix(baseColor, grout_color, n * noiseWeight) : baseColor;
}

float TileMaterial::GetHeight(glm::vec2 uv)
{
    int w = grid.size();
    float gridWidth = tile_width + 2.0f * grout_width;
    float patternWidth = w * gridWidth;

    // Wrap the projected space of the whole texture
    float u = properFMod(uv.x, patternWidth);
    float v = properFMod(uv.y, patternWidth);

    // Check to see if we are in a grout area by 'wrapping' a grid space
    float g = properFMod(uv.x, gridWidth);
    float r = properFMod(uv.y, gridWidth);

    // Move to grid space to check color value
    u /= gridWidth;
    v /= gridWidth;

    int uu = int(std::floor(u));
    int vv = int(std::floor(v));

    // Check if we are near any edges of the grid space, store it's cardinal grid direction if we are
    int gg = 0;
    int rr = 0;

    if (g <= grout_width) gg = -1;
    else if (g > grout_width + tile_width) gg = 1;

    if (r <= grout_width) rr = -1;
    else if (r > grout_width + tile_width) rr = 1;

    // If we do have a neighbor, compare it to our tile
    if (gg || rr)
    {
        gg = (uu + gg) % w;
        rr = (vv + rr) % w;

        if (gg < 0) gg += w;
        if (rr < 0) rr += w;

        // If the neighboring tile is NOT the same type of tile, we've reached some grout
        if (grid[gg][rr] != grid[uu][vv])
        {
            // Add a small bevel to the edges, it's not super noticable... 
            // ...but it does remove some artifacts as opposed to just returning 0.0f
            float edgeU = glm::smoothstep(0.0f, grout_width, g) *
                (1.0f - glm::smoothstep(tile_width + grout_width, gridWidth, g));

            float edgeV = glm::smoothstep(0.0f, grout_width, r) *
                (1.0f - glm::smoothstep(tile_width + grout_width, gridWidth, r));


            return edgeU * edgeV;
        }
    }

    return 1.0f;
}

glm::vec3 TileMaterial::PerturbNormal(glm::vec2 uv, glm::vec3 normal)
{
    float eps = 0.005f;
    float bumpScale = 2.0f;

    // Add a small gradient to break up the uniform look
    float h = GetHeight(uv);
    float hx = GetHeight(uv + glm::vec2(eps, 0.0f));
    float hy = GetHeight(uv + glm::vec2(0.0f, eps));

    float dhdu = hx - h;
    float dhdv = hy - h;

    // Most normal maps seem to include tangent and bitangent. For a quick and dirty procedural texture, this is fine for now
    glm::vec3 gradient = dhdu * glm::vec3(1.0f, 0.0f, 0.0f) 
                        + dhdv * glm::vec3(0.0f, 0.0f, 1.0f);

    return glm::normalize(normal - bumpScale * gradient);
}

TileMaterial::TileMaterial(float kr, float kt, float wTile, float wGrout, 
    glm::vec3 c1, glm::vec3 c2, glm::vec3 cGrout, glm::vec3 s)
{
    reflectance = kr;
    transmission = kt;
    tile_width = wTile;
    grout_width = wGrout;
    color_option_1 = c1;
    color_option_2 = c2;
    grout_color = cGrout;
    specular = s;

    noise = SimplexNoise();
    noise.setSeed(noiseSeed);
}