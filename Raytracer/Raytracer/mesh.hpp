#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>
#include "world.hpp"

// CREDITS: The mesh class is based upon OGLDEV's assimp tutorial here https://www.youtube.com/watch?v=sP_kiODC25Q

#define ARRAY_NUM_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

// Turn quads into triangles
// Smooth lighting (might not need since this is a raycaster)
// Flip texture coords, some modelers allow this, might need to play with it a bit
// Adjusts the index buffer if there are identical vertices
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)


// TODO: add a texture class to our model
// TODO: mesh should be considered a "single object" that should use some sort of initial...
// ... AABB or circle collision, which then looks for the triangle within itself...
// ... with perhaps individual limbs of the mesh (if any) are further bounding boxes or colliders

class Mesh {
public:
	Mesh() {};
	~Mesh();

	bool LoadMesh(const std::string& Filename);

	void Render(World world);

	//bool GetWorldTransform() { return m_worldTransform; }
private:
	void Clear();

	bool InitFromScene(const aiScene* pScene, const std::string& Filename);

	void CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices);

	void ReserveSpace(unsigned int NumVertices, unsigned int NumIndices);

	void InitAllMeshes(const aiScene* pScene);

	void InitSingleMesh(const aiMesh* paiMesh);

	bool InitMaterials(const aiScene* pScene, const std::string& Filename);

	void PopulateBuffers();

	enum BUFFER_TYPE {
		INDEX_BUFFER = 0,
		POS_VB = 1,
		TEXCOORD_VB = 2,
		NORMAL_VB = 3,		// temp 
		WVP_MAT_VB = 4,		// temp
		WORLD_MAT_VB = 5,	// temp
		NUM_BUFFERS = 6
	};

	// m_worldTransform The world transform
	unsigned int m_Buffers[NUM_BUFFERS] = { 0 };

	struct BasicMeshEntry {
		BasicMeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = 0;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

	/// <summary>
	/// A list of each of the submeshes in our overall object (Human->body, arm1, arm2, leg1, etc.)
	/// </summary>
	std::vector<BasicMeshEntry> m_Meshes;
	//std::vector<Texture*> m_Textures;

	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_TexCoords;
	std::vector<glm::vec3> m_Indices;
};