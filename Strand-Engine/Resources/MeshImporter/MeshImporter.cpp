// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "MeshImporter.hpp"

#include <Resources/Mesh/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Strand
{

bool MeshImporter::ReadStaticMeshFile(const std::string& filePath, Mesh* mesh)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << importer.GetErrorString() << "\n";
        return false;
    }

    aiMesh* pMesh;

    if(scene->HasMeshes())
        pMesh = scene->mMeshes[0];

    for(uint32_t i = 0; i < pMesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.Pos.x = pMesh->mVertices[i].x;
        vertex.Pos.y = pMesh->mVertices[i].y;
        vertex.Pos.z = pMesh->mVertices[i].z;

        vertex.UV.x = pMesh->mTextureCoords[0][i].x;
        vertex.UV.y = -pMesh->mTextureCoords[0][i].y;

        mesh->GetVertices().push_back(vertex);
    }

    for(uint32_t i = 0; i < pMesh->mNumFaces; i++) {
        aiFace face = pMesh->mFaces[i];

        for(uint32_t j = 0; j < face.mNumIndices; j++) {
            mesh->GetIndices().push_back(face.mIndices[j]);
        }
    }

    return false;
}

bool MeshImporter::ReadSkeletalMeshFile(const std::string& filePath, Mesh* mesh)
{
    return false;
}

bool MeshImporter::ReadSceneFile(const std::string& filePath, Scene* scene)
{
    return false;
}

bool MeshImporter::ReadTextureFile(const std::string& filePath, Texture* texture)
{
    return false;
}

} // Strand