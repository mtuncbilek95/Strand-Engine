// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/Utils/DxgiUtils.hpp>

namespace Strand
{

enum class RenderTargetViewDimension
{
    UNKNOWN,
    TEXTURE1D,
    TEXTURE1D_ARRAY,
    BUFFER,
    TEXTURE2D,
    TEXTURE2D_ARRAY,
    TEXTURE2D_MULTISAMPLE,
    TEXTURE2D_MULTISAMPLE_ARRAY,
    TEXTURE3D
};

enum class DepthStencilViewDimension
{
    UNKNOWN,
    TEXTURE1D,
    TEXTURE1D_ARRAY,
    TEXTURE2D,
    TEXTURE2D_ARRAY,
    TEXTURE2D_MULTISAMPLE,
    TEXTURE2D_MULTISAMPLE_ARRAY
};

struct FramebufferDesc
{
    DxgiFormat ColorAttachmentFormat_;
    RenderTargetViewDimension ColorAttachmentDimension_;

    DxgiFormat DepthStencilFormat_;
    DepthStencilViewDimension DepthStencilDimension_;

    DXHEAP<ID3D11Texture2D> ColorAttachment_;
    DXHEAP<ID3D11Texture2D> DepthAttachment_;
};

struct FrameBufferUtils
{
    static D3D11_RTV_DIMENSION GetD3D11RTVDimension(RenderTargetViewDimension rtvDimension)
    {
        switch(rtvDimension) {
            case RenderTargetViewDimension::UNKNOWN:
                return D3D11_RTV_DIMENSION_UNKNOWN;
            case RenderTargetViewDimension::BUFFER:
                return D3D11_RTV_DIMENSION_BUFFER;
            case RenderTargetViewDimension::TEXTURE1D:
                return D3D11_RTV_DIMENSION_TEXTURE1D;
            case RenderTargetViewDimension::TEXTURE1D_ARRAY:
                return D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
            case RenderTargetViewDimension::TEXTURE2D:
                return D3D11_RTV_DIMENSION_TEXTURE2D;
            case RenderTargetViewDimension::TEXTURE2D_ARRAY:
                return D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
            case RenderTargetViewDimension::TEXTURE2D_MULTISAMPLE:
                return D3D11_RTV_DIMENSION_TEXTURE2DMS;
            case RenderTargetViewDimension::TEXTURE2D_MULTISAMPLE_ARRAY:
                return D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
            case RenderTargetViewDimension::TEXTURE3D:
                return D3D11_RTV_DIMENSION_TEXTURE3D;
            default:
                return D3D11_RTV_DIMENSION_UNKNOWN;
        }
    }

    static D3D11_DSV_DIMENSION GetD3D11DSVDimension(DepthStencilViewDimension dsvDimension)
    {
        switch(dsvDimension) {
            case DepthStencilViewDimension::UNKNOWN:
                return D3D11_DSV_DIMENSION_UNKNOWN;
            case DepthStencilViewDimension::TEXTURE1D:
                return D3D11_DSV_DIMENSION_TEXTURE1D;
            case DepthStencilViewDimension::TEXTURE1D_ARRAY:
                return D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
            case DepthStencilViewDimension::TEXTURE2D:
                return D3D11_DSV_DIMENSION_TEXTURE2D;
            case DepthStencilViewDimension::TEXTURE2D_ARRAY:
                return D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
            case DepthStencilViewDimension::TEXTURE2D_MULTISAMPLE:
                return D3D11_DSV_DIMENSION_TEXTURE2DMS;
            case DepthStencilViewDimension::TEXTURE2D_MULTISAMPLE_ARRAY:
                return D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
            default:
                return D3D11_DSV_DIMENSION_UNKNOWN;
        }
    }
};

} // Strand
