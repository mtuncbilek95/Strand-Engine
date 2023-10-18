// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Resources/Mesh/MeshDesc.hpp>
namespace Strand
{

class GraphicsBuffer;
class GraphicsDevice;
class CommandList;
struct GraphicsBufferDesc;

// @brief Mesh class
class STRAND_API Mesh
{
public:
    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    ~Mesh() = default;

    void AllocateVertex();
    void AllocateIndex();

    void UpdateVertex();
    void UpdateIndex();

    SharedHeap<GraphicsBuffer> GetPositionBuffer() const { return PositionBuffer_; }
    SharedHeap<GraphicsBuffer> GetNormalBuffer() const { return NormalBuffer_; }
    SharedHeap<GraphicsBuffer> GetTangentBuffer() const { return TangentBuffer_; }
    SharedHeap<GraphicsBuffer> GetBinormalBuffer() const { return BinormalBuffer_; }
    SharedHeap<GraphicsBuffer> GetTexCoordBuffer() const { return TexCoordBuffer_; }
    SharedHeap<GraphicsBuffer> GetIndexBuffer() const { return IndexBuffer_; }

    ArrayList<XMFLOAT3>& GetPositionData() { return PositionData_; }
    ArrayList<XMFLOAT3>& GetNormalData() { return NormalData_; }
    ArrayList<XMFLOAT3>& GetTangentData() { return TangentData_; }
    ArrayList<XMFLOAT3>& GetBinormalData() { return BinormalData_; }
    ArrayList<XMFLOAT2>& GetTexCoordData() { return TexCoordData_; }
    ArrayList<uint16_t>& GetIndexData() { return IndexData_; }

private:

    ArrayList<XMFLOAT3> PositionData_;
    ArrayList<XMFLOAT3> NormalData_;
    ArrayList<XMFLOAT3> TangentData_;
    ArrayList<XMFLOAT3> BinormalData_;
    ArrayList<XMFLOAT2> TexCoordData_;
    ArrayList<uint16_t> IndexData_;

    SharedHeap<GraphicsBuffer> PositionBuffer_;
    SharedHeap<GraphicsBuffer> NormalBuffer_;
    SharedHeap<GraphicsBuffer> TangentBuffer_;
    SharedHeap<GraphicsBuffer> BinormalBuffer_;
    SharedHeap<GraphicsBuffer> TexCoordBuffer_;
    SharedHeap<GraphicsBuffer> IndexBuffer_;

    CommandList* CommandList_;
};

} // Strand
