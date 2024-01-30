#include "MeshLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Runtime/Resource/Mesh/Mesh.h>

namespace Strand
{
	void MeshLoader::LoadSingleMesh(const String& path, SharedPtr<Mesh>& mesh)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			DEV_LOG(SE_ERROR, "Failed to load mesh file: %s", importer.GetErrorString());
			return;
		}

		aiMesh* pMesh = scene->mMeshes[0];

		// If mesh has positions, load positions and indices
		if (pMesh->HasPositions())
		{
			for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
			{
				mesh->mPositions.push_back({ pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z });
			}

			for (uint32 i = 0; i < pMesh->mNumFaces; ++i)
			{
				aiFace face = pMesh->mFaces[i];
				for (uint32 j = 0; j < face.mNumIndices; ++j)
				{
					mesh->mIndices.push_back(face.mIndices[j]);
				}
			}
		}

		// If mesh has normals, load normals
		if (pMesh->HasNormals())
		{
			mesh->mNormals.resize(pMesh->mNumVertices);
			for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
			{
				mesh->mNormals[i] = { pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z };
			}
		}

		// If mesh has tangents and bitangents, load them
		if (pMesh->HasTangentsAndBitangents())
		{
			mesh->mTangents.resize(pMesh->mNumVertices);
			mesh->mBitangents.resize(pMesh->mNumVertices);
			for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
			{
				mesh->mTangents[i] = { pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z };
				mesh->mBitangents[i] = { pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z };
			}
		}

		// If mesh has texture coordinates, load them
		if (pMesh->HasTextureCoords(0))
		{
			mesh->mTexCoords.resize(pMesh->mNumVertices);
			for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
			{
				mesh->mTexCoords[i] = { pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y };
			}
		}

		// If mesh has colors, load them
		if (pMesh->HasVertexColors(0))
		{
			mesh->mColors.resize(pMesh->mNumVertices);
			for (uint32 i = 0; i < pMesh->mNumVertices; ++i)
			{
				mesh->mColors[i] = { pMesh->mColors[0][i].r, pMesh->mColors[0][i].g, pMesh->mColors[0][i].b, pMesh->mColors[0][i].a };
			}
		}

		mesh->AllocateBuffers();
	}

	void MeshLoader::LoadScene(const String& path, SharedPtr<Scene>& scene)
	{
	}
}
