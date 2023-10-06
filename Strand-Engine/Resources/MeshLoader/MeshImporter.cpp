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
    /*Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << importer.GetErrorString() << "\n";
        return false;
    }

    aiMesh* pMesh;

    if(scene->HasMeshes())
        pMesh = scene->mMeshes[0];

    if(pMesh->HasPositions()) {
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.Position = XMVectorSet(pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z, 0.0f);
            if(i % 2 == 0)
                vertex.Color = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
            else if( i % 3 == 0)
                vertex.Color = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
            else if( i % 5 == 0)
                vertex.Color = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
            else if(i % 7 == 0)
                vertex.Color = XMVectorSet(1.0f, 1.0f, 0.0f, 1.0f);
            else
                vertex.Color = XMVectorSet(0.0f, 1.0f, 1.0f, 1.0f);

            mesh->GetVertices().push_back(vertex);
        }
    } else {
        std::cerr << "Mesh has no positions." << std::endl;
        return false;
    }

    if(pMesh->HasFaces()) {
        for(int i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++) {
                mesh->GetIndices().push_back(face.mIndices[j]);
            }
        }
    } else {
        std::cerr << "Mesh has no faces." << std::endl;
        return false;
    }

    return true;
*/

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