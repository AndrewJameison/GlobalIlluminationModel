#pragma once
#include "mesh.hpp"
#include "triangle.hpp"

Mesh::~Mesh()
{
	Clear();
}

void Mesh::Clear()
{
	// Allows us to reuse the same data structure for different meshes, unused for now

	// delete textures
	// delete buffers
	// delete vertex arrays
}

bool Mesh::LoadMesh(const std::string& Filename)
{
	Clear();

	// Create vertex arrays
	// Bind the vertex arrays

	// Create the vertex buffers

	Assimp::Importer Importer;

	bool success = false;
	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), ASSIMP_LOAD_FLAGS);

	if (pScene)
	{
		success = InitFromScene(pScene, Filename);
	}
	else
	{
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
	}

	// Unbind vertex arrays

	return success;
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Meshes.resize(pScene->mNumMeshes);
	// m_Textures.resize(pScene->mNumMaterials);

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	CountVerticesAndIndices(pScene, NumVertices, NumIndices);

	InitAllMeshes(pScene);

	if (!InitMaterials(pScene, Filename)) {
		return false;
	}

	PopulateBuffers();

	return true;
}

/// <summary>
/// Calculates and stores the index locations of the vertices stored in each aiMesh
/// </summary>
/// <param name="pScene"></param>
/// <param name="NumVertices"></param>
/// <param name="NumIndices"></param>
void Mesh::CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices)
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		m_Meshes[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_Meshes[i].BaseVertex = NumVertices;
		m_Meshes[i].BaseIndex = NumIndices;

		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += m_Meshes[i].NumIndices;
	}
}

void Mesh::ReserveSpace(unsigned int NumVertices, unsigned int NumIndices)
{
	m_Positions.reserve(NumVertices);
	m_Normals.reserve(NumVertices);
	m_TexCoords.reserve(NumVertices);
	m_Indices.reserve(NumIndices);
}

void Mesh::InitAllMeshes(const aiScene* pScene)
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitSingleMesh(paiMesh);
	}
}

void Mesh::InitSingleMesh(const aiMesh* paiMesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// Populate the vertex attribute vectors
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D& pPos = paiMesh->mVertices[i];
		const aiVector3D& pNormal = paiMesh->mNormals[i];
		const aiVector3D& pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : Zero3D;

		m_Positions.push_back(glm::vec3(pPos.x, pPos.y, pPos.z));
		m_Normals.push_back(glm::vec3(pNormal.x, pNormal.y, pNormal.z));
		m_TexCoords.push_back(glm::vec2(pTexCoord.x, pTexCoord.y));
	}
	
	// Populate the index buffer
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face->mNumIndices == 3);
		m_Indices.push_back(Face.mIndices[i]);
		m_Indices.push_back(Face.mIndices[1]);
		m_Indices.push_back(Face.mIndices[2]);
	}
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	return false;
}

void Mesh::PopulateBuffers()
{
}

void Mesh::Render(World world)
{
	for (unsigned int i=0; i < m_Meshes.size(); i++)
	{
		//unsigned int MaterialIndex = m_Meshes[i].MaterialIndex;
		//
		//assert(MaterialIndex < m_Texturess.size());
		//
		//if (m_Textures[MaterialIndex])
		//{
		//	m_Textures[MaterialIndex]->Bind(COLOR_TEXTURE_UNIT);
		//}

		// TODO: create and add a triangle to world

		world.Add(new Triangle());
	}
}
