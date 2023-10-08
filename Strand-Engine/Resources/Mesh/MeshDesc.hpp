// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class MeshType
{
    STATIC,
    SKELETAL
};

enum class VertexType
{
    POSITION,
    NORMAL,
    TANGENT,
    BINORMAL,
    TEXCOORD
};

struct MeshDesc
{
    VertexType VertexType_;
    uint64_t ByteWidth;
    uint64_t VertexStride_;

    void* VertexData_;
};

} // Strand
