// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>

namespace Strand
{

enum class InputLayoutSemanticName
{
    POSITION,
    NORMAL,
    TEXCOORD,
    TANGENT,
    BINORMAL,
    COLOR,
    COUNT
};

enum class InputSlotClass
{
    PER_VERTEX_DATA,
    PER_INSTANCE_DATA
};

enum class MeshTopology
{
    POINT_LIST,
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP
};

struct STRAND_API InputLayoutDesc
{
    ArrayList<InputLayoutSemanticName> SemanticName_;
    ArrayList<DxgiFormat> InputFormat;
    ArrayList<uint32_t> SemanticIndex_;
    ArrayList<uint32_t> InputSlot_;
    ArrayList<uint32_t> AlignedByteOffset_;
    ArrayList<InputSlotClass> InputSlotClass_;
    ArrayList<uint32_t> InstanceDataStepRate_;
    MeshTopology MeshTopology_;
};

struct InputLayoutUtils
{
    static D3D11_INPUT_CLASSIFICATION GetInputClassification(InputSlotClass slotClass)
    {
        switch(slotClass)
        {
            case InputSlotClass::PER_VERTEX_DATA:
                return D3D11_INPUT_PER_VERTEX_DATA;
            case InputSlotClass::PER_INSTANCE_DATA:
                return D3D11_INPUT_PER_INSTANCE_DATA;
            default:
                return D3D11_INPUT_PER_VERTEX_DATA;
        }
    }

    static D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology(MeshTopology topology)
    {
        switch(topology)
        {
            case MeshTopology::POINT_LIST:
                return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
            case MeshTopology::LINE_LIST:
                return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
            case MeshTopology::LINE_STRIP:
                return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
            case MeshTopology::TRIANGLE_LIST:
                return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
            case MeshTopology::TRIANGLE_STRIP:
                return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
            default:
                return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        }
    }
};

} // Strand
