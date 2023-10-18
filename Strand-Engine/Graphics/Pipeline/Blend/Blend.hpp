// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{
enum class BlendType
{
    ZERO,
    ONE,
    SRC_COLOR,
    INV_SRC_COLOR,
    SRC_ALPHA,
    INV_SRC_ALPHA,
    DEST_ALPHA,
    INV_DEST_ALPHA,
    DEST_COLOR,
    INV_DEST_COLOR,
    SRC_ALPHA_SAT,
    BLEND_FACTOR,
    INV_BLEND_FACTOR,
    SRC1_COLOR,
    INV_SRC1_COLOR,
    SRC1_ALPHA,
    INV_SRC1_ALPHA
};

enum class BlendOperation
{
    ADD,
    SUBTRACT,
    REV_SUBTRACT,
    MIN,
    MAX
};

enum class ColorWriteEnable
{
    RED = 1,
    GREEN = 2,
    BLUE = 4,
    ALPHA = 8,
    ALL = (((RED | GREEN) | BLUE) | ALPHA)
};

struct RenderTargetBlendDesc
{
    bool BlendEnable_;
    BlendType SrcBlend_;
    BlendType DestBlend_;
    BlendOperation BlendOp_;
    BlendType SrcBlendAlpha_;
    BlendType DestBlendAlpha_;
    BlendOperation BlendOpAlpha_;
    ColorWriteEnable RenderTargetWriteMask_;
};

struct BlendStateDesc
{
    bool AlphaToCoverageEnable_;
    bool IndependentBlendEnable_;
    RenderTargetBlendDesc RenderTargetDesc_;
};

struct BlendUtil
{
    static D3D11_BLEND GetBlendType(BlendType type)
    {
        switch(type) {
            case BlendType::ZERO:
                return D3D11_BLEND_ZERO;
            case BlendType::ONE:
                return D3D11_BLEND_ONE;
            case BlendType::SRC_COLOR:
                return D3D11_BLEND_SRC_COLOR;
            case BlendType::INV_SRC_COLOR:
                return D3D11_BLEND_INV_SRC_COLOR;
            case BlendType::SRC_ALPHA:
                return D3D11_BLEND_SRC_ALPHA;
            case BlendType::INV_SRC_ALPHA:
                return D3D11_BLEND_INV_SRC1_COLOR;
            case BlendType::DEST_ALPHA:
                return D3D11_BLEND_DEST_ALPHA;
            case BlendType::INV_DEST_ALPHA:
                return D3D11_BLEND_INV_DEST_ALPHA;
            case BlendType::DEST_COLOR:
                return D3D11_BLEND_DEST_COLOR;
            case BlendType::INV_DEST_COLOR:
                return D3D11_BLEND_INV_DEST_COLOR;
            case BlendType::SRC_ALPHA_SAT:
                return D3D11_BLEND_SRC_ALPHA_SAT;
            case BlendType::BLEND_FACTOR:
                return D3D11_BLEND_BLEND_FACTOR;
            case BlendType::INV_BLEND_FACTOR:
                return D3D11_BLEND_INV_BLEND_FACTOR;
            case BlendType::SRC1_COLOR:
                return D3D11_BLEND_SRC1_COLOR;
            case BlendType::INV_SRC1_COLOR:
                return D3D11_BLEND_INV_SRC1_COLOR;
            case BlendType::SRC1_ALPHA:
                return D3D11_BLEND_SRC1_ALPHA;
            case BlendType::INV_SRC1_ALPHA:
                return D3D11_BLEND_INV_SRC1_ALPHA;
            default:
                return D3D11_BLEND_ZERO;
        }
    }

    static D3D11_BLEND_OP GetBlendOp(BlendOperation op)
    {
        switch(op) {
            case BlendOperation::ADD:
                return D3D11_BLEND_OP_ADD;
            case BlendOperation::SUBTRACT:
                return D3D11_BLEND_OP_SUBTRACT;
            case BlendOperation::REV_SUBTRACT:
                return D3D11_BLEND_OP_REV_SUBTRACT;
            case BlendOperation::MIN:
                return D3D11_BLEND_OP_MIN;
            case BlendOperation::MAX:
                return D3D11_BLEND_OP_MAX;
            default:
                return D3D11_BLEND_OP_ADD;
        }
    }

    static D3D11_COLOR_WRITE_ENABLE GetColorWriteEnable(ColorWriteEnable enable)
    {
        switch(enable) {
            case ColorWriteEnable::RED:
                return D3D11_COLOR_WRITE_ENABLE_RED;
            case ColorWriteEnable::GREEN:
                return D3D11_COLOR_WRITE_ENABLE_GREEN;
            case ColorWriteEnable::BLUE:
                return D3D11_COLOR_WRITE_ENABLE_BLUE;
            case ColorWriteEnable::ALPHA:
                return D3D11_COLOR_WRITE_ENABLE_ALPHA;
            case ColorWriteEnable::ALL:
                return D3D11_COLOR_WRITE_ENABLE_ALL;
            default:
                return D3D11_COLOR_WRITE_ENABLE_ALL;
        }
    }
};

} // Strand
