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

    switch (grid[uu][vv])
    {
        case Slab1:
        case Slab2:
        case Slab3:
        case Slab4:
        case Square2:
        case Vert4:
            return color_option_2;

        default:
            return color_option_1;
    }
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
}