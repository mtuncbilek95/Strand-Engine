// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "MeshLoader.hpp"

#include <Resources/Mesh/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Strand
{

bool MeshLoader::ReadStaticMeshFile(const std::string& filePath, Mesh* mesh)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return false;
    }

    if(!scene->HasMeshes()) {
        return false;
    }

    aiMesh* pMesh = scene->mMeshes[0];

    if(!pMesh->HasBones()) {

        mesh->SetType(MeshType::Static);

        // Find Vertices for each face
        for(unsigned int i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];

            for(unsigned int j = 0; j < face.mNumIndices; j++) {
                aiVector3D vertex = pMesh->mVertices[face.mIndices[j]];
                aiVector3D normal = pMesh->mNormals[face.mIndices[j]];
                aiVector3D texCoord = pMesh->mTextureCoords[0][face.mIndices[j]];

                Vertex v;
                v.Position = XMVectorSet(vertex.x, vertex.y, vertex.z, 1.0f);
                v.Normal = XMVectorSet(normal.x, normal.y, normal.z, 1.0f);
                v.TexCoord = XMVectorSet(texCoord.x, texCoord.y, texCoord.z, 1.0f);

                mesh->GetVertices().push_back(v);
            }
        }

        // Find Indices for each face
        for(unsigned int i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];

            for(unsigned int j = 0; j < face.mNumIndices; j++) {
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