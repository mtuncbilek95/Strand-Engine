// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class FillMode
{
    WIRE_FRAME,
    SOLID
};

enum class CullMode
{
    NONE,
    FRONT,
    BACK
};

enum class FrontFace
{
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

struct RasterizerStateDesc
{
    FillMode FillMode_;
    CullMode CullMode_;
    FrontFace FrontFace_;
    int DepthBias_;
    float DepthBiasClamp_;
    float SlopeScaledDepthBias_;
    bool DepthClipEnable_;
    bool ScissorEnable_;
    bool MultisampleEnable_;
    bool AntialiasedLineEnable_;
};

struct RasterizerStateUtils
{
    static D3D11_FILL_MODE GetFillMode(FillMode fillMode)
    {
        switch (fillMode)
        {
        case FillMode::WIRE_FRAME:
            return D3D11_FILL_WIREFRAME;
        case FillMode::SOLID:
            return D3D11_FILL_SOLID;
        default:
            return D3D11_FILL_WIREFRAME;
        }
    }

    static D3D11_CULL_MODE GetCullMode(CullMode cullMode)
    {
        switch (cullMode)
        {
        case CullMode::NONE:
            return D3D11_CULL_NONE;
        case CullMode::FRONT:
            return D3D11_CULL_FRONT;
        case CullMode::BACK:
            return D3D11_CULL_BACK;
        default:
            return D3D11_CULL_NONE;
        }
    }

    static bool GetFrontFace(FrontFace frontFace)
    {
        switch (frontFace)
        {
        case FrontFace::CLOCKWISE:
            return false;
        case FrontFace::COUNTER_CLOCKWISE:
            return true;
        default:
            return false;
        }
    }

};

} // Strand
