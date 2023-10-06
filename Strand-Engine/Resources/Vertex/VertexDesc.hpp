// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once
namespace Strand
{

enum class VertexType
{
    POSITION,
    COLOR,
    NORMAL,
    TANGENT,
    BINORMAL,
    TEXCOORD,
    UNKNOWN
};

struct VertexTypeDesc
{
    VertexType type;
    uint32_t offset;
    uint32_t size;
};

} // Strand
