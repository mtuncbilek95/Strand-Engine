// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Mesh.hpp"

#include <Graphics/Manager/GraphicsManager.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <Common/Log.hpp>

namespace Strand
{


void Mesh::AllocateVertex(std::vector<MeshDesc> VertexDesc)
{

    MeshDescs_ = VertexDesc;

    for(int i = 0; i < MeshDescs_.size(); i++) {
        GraphicsBufferDesc desc = {
                .Usage = ResourceUsage::DEFAULT,
                .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
                .BindFlags = ResourceBindFlags::VERTEX_BUFFER,
                .MiscFlags = 0,
                .ByteWidth = MeshDescs_[i].ByteWidth,
                .StructureByteStride = MeshDescs_[i].VertexStride_,
                .CPUData = MeshDescs_[i].VertexData_
        };

        switch(MeshDescs_[i].VertexType_)
        {
            case VertexType::POSITION:
                PositionBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
                break;
            case VertexType::NORMAL:
                NormalBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
                break;
            case VertexType::TANGENT:
                TangentBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
                break;
            case VertexType::BINORMAL:
                BinormalBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
                break;
            case VertexType::TEXCOORD:
                TexCoordBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
                break;
            default:
                std::cerr << "Invalid VertexType!\n";
                break;
        }
    }
}

void Mesh::AllocateIndex(MeshDesc indexDesc)
{
    IndexDesc_ = indexDesc;

    GraphicsBufferDesc desc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::INDEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = IndexDesc_.ByteWidth,
            .StructureByteStride = IndexDesc_.VertexStride_,
            .CPUData = IndexDesc_.VertexData_
    };

    IndexBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
}

void Mesh::UpdateVertex()
{

}

void Mesh::UpdateIndex()
{

}

} // Strand