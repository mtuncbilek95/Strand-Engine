// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "MeshImporter.hpp"

#include <Resources/Mesh/Mesh.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBufferDesc.hpp>

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

    // If mesh has positions, create Mesh Desc for both Position and Index Buffer.
    if(pMesh->HasPositions()) {
        mesh->GetPositionData().resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            mesh->GetPositionData()[i] = {pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z};
        }

        for(int i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++)
                mesh->GetIndexData().push_back(face.mIndices[j]);
        }
    }

    // Create MeshDesc for TexCoord Buffer.
    if(pMesh->HasTextureCoords(0)) {
        mesh->GetTexCoordData().resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            mesh->GetTexCoordData()[i] = {pMesh->mTextureCoords[0][i].x, -pMesh->mTextureCoords[0][i].y};
        }
    }

    // Create MeshDesc for Normal Buffer.
    if(pMesh->HasNormals()) {
        mesh->GetNormalData().resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            mesh->GetNormalData()[i] = {pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z};
        }

    }

    // Create MeshDesc for Tangent Buffer.
    if(pMesh->HasTangentsAndBitangents()) {
        mesh->GetTangentData().resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            mesh->GetTangentData()[i] = {pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z};
        }
    }

    // Create MeshDesc for Binormal Buffer.
    if(pMesh->HasTangentsAndBitangents()) {
        mesh->GetBinormalData().resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            mesh->GetBinormalData()[i] = {pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z};
        }

    }

    mesh->AllocateVertex();
    mesh->AllocateIndex();

    return true;
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