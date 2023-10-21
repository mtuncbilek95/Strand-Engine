// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class DepthWriteMask
{
    ZERO,
    ALL
};

enum class DepthStencilComparisonFunc
{
    NEVER,
    LESS,
    EQUAL,
    LESS_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATER_EQUAL,
    ALWAYS
};

struct STRAND_API DepthStencilStateDesc
{
    bool DepthEnable_;
    DepthWriteMask DepthWriteMask_;
    DepthStencilComparisonFunc DepthFunc_;
    bool StencilEnable_;
    uint8_t StencilReadMask_;
    uint8_t StencilWriteMask_;
};

struct DepthStencilUtils
{
    static D3D11_DEPTH_WRITE_MASK GetDepthWriteMask(DepthWriteMask mask)
    {
        switch (mask)
        {
        case DepthWriteMask::ZERO:
            return D3D11_DEPTH_WRITE_MASK_ZERO;
        case DepthWriteMask::ALL:
            return D3D11_DEPTH_WRITE_MASK_ALL;
        default:
            return D3D11_DEPTH_WRITE_MASK_ZERO;
        }
    }

    static D3D11_COMPARISON_FUNC GetComparisonFunc(DepthStencilComparisonFunc func)
    {
        switch (func)
        {
        case DepthStencilComparisonFunc::NEVER:
            return D3D11_COMPARISON_NEVER;
        case DepthStencilComparisonFunc::LESS:
            return D3D11_COMPARISON_LESS;
        case DepthStencilComparisonFunc::EQUAL:
            return D3D11_COMPARISON_EQUAL;
        case DepthStencilComparisonFunc::LESS_EQUAL:
            return D3D11_COMPARISON_LESS_EQUAL;
        case DepthStencilComparisonFunc::GREATER:
            return D3D11_COMPARISON_GREATER;
        case DepthStencilComparisonFunc::NOT_EQUAL:
            return D3D11_COMPARISON_NOT_EQUAL;
        case DepthStencilComparisonFunc::GREATER_EQUAL:
            return D3D11_COMPARISON_GREATER_EQUAL;
        case DepthStencilComparisonFunc::ALWAYS:
            return D3D11_COMPARISON_ALWAYS;
        default:
            return D3D11_COMPARISON_NEVER;
        }
    }
};

} // Strand
