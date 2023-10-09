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

    void AllocateVertex();
    void AllocateIndex();

    void UpdateVertex();
    void UpdateIndex();

    GraphicsBuffer* GetPositionBuffer() const { return PositionBuffer_; }
    GraphicsBuffer* GetNormalBuffer() const { return NormalBuffer_; }
    GraphicsBuffer* GetTangentBuffer() const { return TangentBuffer_; }
    GraphicsBuffer* GetBinormalBuffer() const { return BinormalBuffer_; }
    GraphicsBuffer* GetTexCoordBuffer() const { return TexCoordBuffer_; }
    GraphicsBuffer* GetIndexBuffer() const { return IndexBuffer_; }

    std::vector<XMFLOAT3>& GetPositionData() { return PositionData_; }
    std::vector<XMFLOAT3>& GetNormalData() { return NormalData_; }
    std::vector<XMFLOAT3>& GetTangentData() { return TangentData_; }
    std::vector<XMFLOAT3>& GetBinormalData() { return BinormalData_; }
    std::vector<XMFLOAT2>& GetTexCoordData() { return TexCoordData_; }
    std::vector<uint16_t>& GetIndexData() { return IndexData_; }

private:

    std::vector<XMFLOAT3> PositionData_;
    std::vector<XMFLOAT3> NormalData_;
    std::vector<XMFLOAT3> TangentData_;
    std::vector<XMFLOAT3> BinormalData_;
    std::vector<XMFLOAT2> TexCoordData_;
    std::vector<uint16_t> IndexData_;

    GraphicsBuffer* PositionBuffer_;
    GraphicsBuffer* NormalBuffer_;
    GraphicsBuffer* TangentBuffer_;
    GraphicsBuffer* BinormalBuffer_;
    GraphicsBuffer* TexCoordBuffer_;
    GraphicsBuffer* IndexBuffer_;

    DXHEAP<ID3D11CommandList> CommandList_;
};

} // Strand
