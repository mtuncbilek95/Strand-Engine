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
    std::vector<MeshDesc> meshArray;
    MeshDesc meshIndex;

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
        std::vector<XMFLOAT3> positions;
        positions.resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            positions[i] = {pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z};
        }

        MeshDesc desc = {
                .VertexType_ = VertexType::POSITION,
                .ByteWidth = sizeof(XMFLOAT3) * positions.size(),
                .VertexStride_ = sizeof(XMFLOAT3),
                .VertexData_ = positions.data()
        };

        meshArray.push_back(desc);

        std::vector<uint16_t> indexArray;

        for(int i = 0; i < pMesh->mNumFaces; i++) {
            aiFace face = pMesh->mFaces[i];
            for(int j = 0; j < face.mNumIndices; j++)
                indexArray.push_back(face.mIndices[j]);
        }

        meshIndex = {
                .VertexType_ = VertexType::POSITION,
                .ByteWidth = sizeof(uint16_t) * indexArray.size(),
                .VertexStride_ = sizeof(uint16_t),
                .VertexData_ = indexArray.data()
        };
    }

    // Create MeshDesc for TexCoord Buffer.
    if(pMesh->HasTextureCoords(0)) {
        std::vector<XMFLOAT2> texCoords;
        texCoords.resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            texCoords[i] = {pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y};
        }

        MeshDesc desc = {
                .VertexType_ = VertexType::TEXCOORD,
                .ByteWidth = sizeof(XMFLOAT2) * pMesh->mNumVertices,
                .VertexStride_ = sizeof(XMFLOAT2),
                .VertexData_ = texCoords.data()
        };

        meshArray.push_back(desc);
    }

    // Create MeshDesc for Normal Buffer.
    if(pMesh->HasNormals()) {
        std::vector<XMFLOAT3> normals;
        normals.resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            normals[i] = {pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z};
        }

        MeshDesc desc = {
                .VertexType_ = VertexType::NORMAL,
                .ByteWidth = sizeof(XMFLOAT3) * pMesh->mNumVertices,
                .VertexStride_ = sizeof(XMFLOAT3),
                .VertexData_ = normals.data()
        };

        meshArray.push_back(desc);
    }

    // Create MeshDesc for Tangent Buffer.
    if(pMesh->HasTangentsAndBitangents()) {
        std::vector<XMFLOAT3> tangents;
        tangents.resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            tangents[i] = {pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z};
        }

        MeshDesc desc = {
                .VertexType_ = VertexType::TANGENT,
                .ByteWidth = sizeof(XMFLOAT3) * pMesh->mNumVertices,
                .VertexStride_ = sizeof(XMFLOAT3),
                .VertexData_ = tangents.data()
        };

        meshArray.push_back(desc);
    }

    // Create MeshDesc for Binormal Buffer.
    if(pMesh->HasTangentsAndBitangents()) {
        std::vector<XMFLOAT3> binormals;
        binormals.resize(pMesh->mNumVertices);
        for(int i = 0; i < pMesh->mNumVertices; i++) {
            binormals[i] = {pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z};
        }

        MeshDesc desc = {
                .VertexType_ = VertexType::BINORMAL,
                .ByteWidth = sizeof(XMFLOAT3) * pMesh->mNumVertices,
                .VertexStride_ = sizeof(XMFLOAT3),
                .VertexData_ = binormals.data()
        };

        meshArray.push_back(desc);
    }

    mesh->AllocateVertex(meshArray);
    mesh->AllocateIndex(meshIndex);

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