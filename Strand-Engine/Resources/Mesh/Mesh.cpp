// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Mesh.hpp"

#include <Graphics/Manager/GraphicsManager.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <Common/Log.hpp>

namespace Strand
{


void Mesh::AllocateVertex()
{
    GraphicsBufferDesc desc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::VERTEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = PositionData_.size() * sizeof(XMFLOAT3),
            .StructureByteStride = sizeof(XMFLOAT3),
            .CPUData = PositionData_.data()
    };

    if(PositionData_.size() != 0)
        PositionBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);

    desc.ByteWidth = NormalData_.size() * sizeof(XMFLOAT3);
    desc.CPUData = NormalData_.data();

    if(NormalData_.size() != 0)
        NormalBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);

    desc.ByteWidth = TangentData_.size() * sizeof(XMFLOAT3);
    desc.CPUData = TangentData_.data();

    if(TangentData_.size() != 0)
        TangentBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);

    desc.ByteWidth = BinormalData_.size() * sizeof(XMFLOAT3);
    desc.CPUData = BinormalData_.data();

    if(BinormalData_.size() != 0)
        BinormalBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);

    desc.ByteWidth = TexCoordData_.size() * sizeof(XMFLOAT2);
    desc.CPUData = TexCoordData_.data();
    desc.StructureByteStride = sizeof(XMFLOAT2);

    if(TexCoordData_.size() != 0)
        TexCoordBuffer_ = GraphicsManager::GetInstance().GetGraphicsDevice()->CreateGraphicsBuffer(desc);
}

void Mesh::AllocateIndex()
{
    GraphicsBufferDesc desc = {
            .Usage = ResourceUsage::DEFAULT,
            .CPUAccessFlags = ResourceCPUAccessFlags::NONE,
            .BindFlags = ResourceBindFlags::INDEX_BUFFER,
            .MiscFlags = 0,
            .ByteWidth = IndexData_.size() * sizeof(uint16_t),
            .StructureByteStride = sizeof(uint16_t),
            .CPUData = IndexData_.data()
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