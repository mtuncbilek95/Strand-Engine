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
    Mesh();
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    ~Mesh() = default;

    void AllocateVertex(GraphicsBufferDesc desc, MeshVertexType type);
    void AllocateIndex(const void** data, uint32_t size);

    void UpdateVertex();
    void UpdateIndex();

private:
    MeshType Type_;

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