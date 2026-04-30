#pragma once
#include "material.hpp"

enum Tile {
	Square1,
	Square2,
	Square3,
	Vert1,
	Vert2,
	Vert3,
	Vert4,
	Slab1,
	Slab2,
	Slab3,
	Slab4,
	Slab5,
	XLSquare
};
/// <summary>
/// A procedurally generated tile material
/// </summary>
class TileMaterial : public Material {

public:
	glm::vec3 GetDiffuse(glm::vec2 uv) override;
	glm::vec3 GetSpecular() override { return specular; }

	TileMaterial(float kr, float kt, float wTile = 2.0f, float wGrout = 0.05,
		glm::vec3 c1 = glm::vec3(255.0f / 256.f, 198.f / 256.f, 133.f / 256.f),
		glm::vec3 c2 = glm::vec3(95.f / 256.f),
		glm::vec3 cGrout = glm::vec3(195.f / 256.f),
		glm::vec3 s = glm::vec3(1.0f));
private:
	float tile_width;
	float grout_width;
	glm::vec3 color_option_1;
	glm::vec3 color_option_2;
	glm::vec3 grout_color;

	std::vector<std::vector<Tile>> grid = {
		{ Slab1,	Slab1,		Vert1,	Slab2, Slab2	},
		{ Vert2,	Square1,	Vert1,	Slab3, Slab3	},
		{ Vert2,	Slab4,		Slab4,	Vert3, Square2	},
		{ XLSquare, XLSquare,	Square3,Vert3, Vert4	},
		{ XLSquare, XLSquare,	Slab5,	Slab5, Vert4	}
	};
	std::vector<std::vector<Tile>> grid_O = {
		{ Square1,	Square2,	Square1,	Square2, Square1	},
		{ Square2,	Square1,	Square2,	Square1, Square2	},
		{ Square1,	Square2,		Square1,	Square2, Square1	},
		{ Square2, Square1,	Square2,Square1, Square2	},
		{ XLSquare, Square2,	Square1,	Square2, Square1	}
	};
};