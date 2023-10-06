// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Resources/Mesh/MeshDesc.hpp>
namespace Strand
{

class GraphicsBuffer;
class GraphicsDevice;

// @brief Mesh class
class STRAND_API Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    virtual MeshType GetType() = 0;

private:
    MeshType Type_;
    GraphicsBuffer* VertexBuffer_;
    GraphicsBuffer* IndexBuffer_;
    GraphicsDevice* Device_;
};

} // Strand

