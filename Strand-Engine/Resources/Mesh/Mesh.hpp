// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Resources/Mesh/MeshDesc.hpp>
namespace Strand
{

class GraphicsBuffer;
class GraphicsDevice;
struct GraphicsBufferDesc;

// @brief Mesh class
class STRAND_API Mesh
{
public:
    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    ~Mesh() = default;

    void AllocateVertex(std::vector<MeshDesc> VertexDesc);
    void AllocateIndex(MeshDesc IndexDesc);

    void UpdateVertex();
    void UpdateIndex();

    GraphicsBuffer* GetPositionBuffer() const { return PositionBuffer_; }
    GraphicsBuffer* GetNormalBuffer() const { return NormalBuffer_; }
    GraphicsBuffer* GetTangentBuffer() const { return TangentBuffer_; }
    GraphicsBuffer* GetBinormalBuffer() const { return BinormalBuffer_; }
    GraphicsBuffer* GetTexCoordBuffer() const { return TexCoordBuffer_; }
    GraphicsBuffer* GetIndexBuffer() const { return IndexBuffer_; }

private:
    std::vector<MeshDesc> MeshDescs_;
    MeshDesc IndexDesc_;

    GraphicsBuffer* PositionBuffer_;
    GraphicsBuffer* NormalBuffer_;
    GraphicsBuffer* TangentBuffer_;
    GraphicsBuffer* BinormalBuffer_;
    GraphicsBuffer* TexCoordBuffer_;
    GraphicsBuffer* IndexBuffer_;

    DXHEAP<ID3D11CommandList> CommandList_;
};

} // Strand

// Allocate vertex index
// Update vertex index

// Two method