// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "MeshLoader.hpp"

#include <Resources/Mesh/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>

namespace Strand
{

bool MeshLoader::ReadStaticMeshFile(const std::string& filePath, Mesh* mesh)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return false;
    }

    if(!scene->HasMeshes()) {
        return false;
    }

    aiMesh* pMesh = scene->mMeshes[0];

    if(!pMesh->HasBones()) {

        mesh->SetType(MeshType::Static);

        // Get Vertices
        for(uint32_t i = 0; i < pMesh->mNumVertices; i+2) {
            Vertex vertex;
            vertex.Position = XMVectorSet(pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z, 1.0f);

            if(i % 2 == 0)
                vertex.Color = XMVectorSet(1.0f, 1.0f, 0.0f, 1.0f);
            else
                vertex.Color = XMVectorSet(0.0f, 1.0f, 1.0f, 1.0f);

            mesh->GetVertices().push_back(vertex);
        }

        // Get Indices
        for(uint32_t i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];
            for(uint32_t j = 0; j < face.mNumIndices; j++) {
                mesh->GetIndices().push_back(face.mIndices[j]);
            }
        }
    }

    return true;
}

bool MeshLoader::ReadSkeletalMeshFile(const std::string& filePath, Mesh* mesh)
{
    return false;
}

bool MeshLoader::ReadSceneFile(const std::string& filePath, Scene* scene)
{
    return false;
}

} // Strand