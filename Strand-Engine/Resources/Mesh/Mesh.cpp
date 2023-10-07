// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Mesh.hpp"

#include <Graphics/Manager/GraphicsManager.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <Common/Log.hpp>

namespace Strand
{

Mesh::Mesh()
{

}

void Mesh::AllocateVertex(GraphicsBufferDesc desc, MeshVertexType type)
{
    switch(type) {
        case MeshVertexType::POSITION:
            PositionBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
            break;
        case MeshVertexType::NORMAL:
            NormalBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
            break;
        case MeshVertexType::TANGENT:
            TangentBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
            break;
        case MeshVertexType::BINORMAL:
            BinormalBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
            break;
        case MeshVertexType::TEXCOORD:
            TexCoordBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
            break;
        default:
            std::cerr << "Invalid MeshVertexType" << std::endl;
            break;
    }
}

void Mesh::AllocateIndex(const void** data, uint32_t size)
{
    GraphicsBufferDesc desc = {
        .Usage = ResourceUsage::DEFAULT,
        .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
        .BindFlags = ResourceBindFlags::INDEX_BUFFER,
        .MiscFlags = 0,
        .ByteWidth = size,
        .StructureByteStride = 0,
        .CPUData = data
    };

    IndexBuffer_ = new GraphicsBuffer(GraphicsManager::GetInstance().GetGraphicsDevice(), desc);
}

void Mesh::UpdateVertex()
{

}

void Mesh::UpdateIndex()
{

}

} // Strand