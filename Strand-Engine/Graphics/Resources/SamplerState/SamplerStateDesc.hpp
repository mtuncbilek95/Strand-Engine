// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class SampleFilter
{
    MIN_MAG_MIP_POINT,
    MIN_MAG_POINT_MIP_LINEAR,
    MIN_POINT_MAG_LINEAR_MIP_POINT,
    MIN_POINT_MAG_MIP_LINEAR,
    MIN_LINEAR_MAG_MIP_POINT,
    MIN_LINEAR_MAG_POINT_MIP_LINEAR,
    MIN_MAG_LINEAR_MIP_POINT,
    MIN_MAG_MIP_LINEAR,
    ANISOTROPIC,
    COMPARISON_MIN_MAG_MIP_POINT,
    COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
    COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
    COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
    COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
    COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
    COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
    COMPARISON_MIN_MAG_MIP_LINEAR,
    COMPARISON_ANISOTROPIC,
    MINIMUM_MIN_MAG_MIP_POINT,
    MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
    MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
    MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
    MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
    MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
    MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
    MINIMUM_MIN_MAG_MIP_LINEAR,
    MINIMUM_ANISOTROPIC,
    MAXIMUM_MIN_MAG_MIP_POINT,
    MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
    MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
    MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
    MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
    MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
    MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
    MAXIMUM_MIN_MAG_MIP_LINEAR,
    MAXIMUM_ANISOTROPIC
};

enum class TextureAddressMode
{
    WRAP,
    MIRROR,
    CLAMP,
    BORDER,
    MIRROR_ONCE
};

enum class SamplerComparisonFunc
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

struct STRAND_API SamplerStateDesc
{
    SampleFilter SamplerFilter_;
    TextureAddressMode AddressModeU_;
    TextureAddressMode AddressModeV_;
    TextureAddressMode AddressModeW_;
    float MipLODBias_;
    uint32_t MaxAnisotropy_;
    SamplerComparisonFunc ComparisonFunc_;
    float BorderColor_[4];
    float MinLOD_;
    float MaxLOD_;
};

struct SamplerStateUtils
{
    static D3D11_FILTER GetSampleFilter(SampleFilter filter)
    {
        switch(filter) {
            case SampleFilter::MIN_MAG_MIP_POINT:
                return D3D11_FILTER_MIN_MAG_MIP_POINT;
            case SampleFilter::MIN_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MIN_POINT_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MIN_POINT_MAG_MIP_LINEAR:
                return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
            case SampleFilter::MIN_LINEAR_MAG_MIP_POINT:
                return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
            case SampleFilter::MIN_LINEAR_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MIN_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MIN_MAG_MIP_LINEAR:
                return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            case SampleFilter::ANISOTROPIC:
                return D3D11_FILTER_ANISOTROPIC;
            case SampleFilter::COMPARISON_MIN_MAG_MIP_POINT:
                return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
            case SampleFilter::COMPARISON_MIN_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
            case SampleFilter::COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
            case SampleFilter::COMPARISON_MIN_POINT_MAG_MIP_LINEAR:
                return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
            case SampleFilter::COMPARISON_MIN_LINEAR_MAG_MIP_POINT:
                return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
            case SampleFilter::COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            case SampleFilter::COMPARISON_MIN_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
            case SampleFilter::COMPARISON_MIN_MAG_MIP_LINEAR:
                return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
            case SampleFilter::COMPARISON_ANISOTROPIC:
                return D3D11_FILTER_COMPARISON_ANISOTROPIC;
            case SampleFilter::MINIMUM_MIN_MAG_MIP_POINT:
                return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
            case SampleFilter::MINIMUM_MIN_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MINIMUM_MIN_POINT_MAG_MIP_LINEAR:
                return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
            case SampleFilter::MINIMUM_MIN_LINEAR_MAG_MIP_POINT:
                return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
            case SampleFilter::MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MINIMUM_MIN_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MINIMUM_MIN_MAG_MIP_LINEAR:
                return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
            case SampleFilter::MINIMUM_ANISOTROPIC:
                return D3D11_FILTER_MINIMUM_ANISOTROPIC;
            case SampleFilter::MAXIMUM_MIN_MAG_MIP_POINT:
                return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
            case SampleFilter::MAXIMUM_MIN_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MAXIMUM_MIN_POINT_MAG_MIP_LINEAR:
                return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
            case SampleFilter::MAXIMUM_MIN_LINEAR_MAG_MIP_POINT:
                return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
            case SampleFilter::MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
                return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
            case SampleFilter::MAXIMUM_MIN_MAG_LINEAR_MIP_POINT:
                return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
            case SampleFilter::MAXIMUM_MIN_MAG_MIP_LINEAR:
                return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
            case SampleFilter::MAXIMUM_ANISOTROPIC:
                return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
            default:
                return D3D11_FILTER_MIN_MAG_MIP_POINT;
        }
    }

    static D3D11_TEXTURE_ADDRESS_MODE GetTextureAddressMode(TextureAddressMode addressMode)
    {
        switch(addressMode) {
            case TextureAddressMode::WRAP:
                return D3D11_TEXTURE_ADDRESS_WRAP;
            case TextureAddressMode::MIRROR:
                return D3D11_TEXTURE_ADDRESS_MIRROR;
            case TextureAddressMode::CLAMP:
                return D3D11_TEXTURE_ADDRESS_CLAMP;
            case TextureAddressMode::BORDER:
                return D3D11_TEXTURE_ADDRESS_BORDER;
            case TextureAddressMode::MIRROR_ONCE:
                return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
            default:
                return D3D11_TEXTURE_ADDRESS_WRAP;
        }
    }

    static D3D11_COMPARISON_FUNC GetComparisonFunc(SamplerComparisonFunc comparisonFunc)
    {
        switch (comparisonFunc)
        {
            case SamplerComparisonFunc::NEVER:
                return D3D11_COMPARISON_NEVER;
            case SamplerComparisonFunc::LESS:
                return D3D11_COMPARISON_LESS;
            case SamplerComparisonFunc::EQUAL:
                return D3D11_COMPARISON_EQUAL;
            case SamplerComparisonFunc::LESS_EQUAL:
                return D3D11_COMPARISON_LESS_EQUAL;
            case SamplerComparisonFunc::GREATER:
                return D3D11_COMPARISON_GREATER;
            case SamplerComparisonFunc::NOT_EQUAL:
                return D3D11_COMPARISON_NOT_EQUAL;
            case SamplerComparisonFunc::GREATER_EQUAL:
                return D3D11_COMPARISON_GREATER_EQUAL;
            case SamplerComparisonFunc::ALWAYS:
                return D3D11_COMPARISON_ALWAYS;
            default:
                return D3D11_COMPARISON_NEVER;
        }
    }
};

} // Strand
