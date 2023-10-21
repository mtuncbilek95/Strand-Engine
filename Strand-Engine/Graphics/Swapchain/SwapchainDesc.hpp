// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/Utils/DxgiUtils.hpp>

namespace Strand
{

enum class DxgiModeScanlineOrder
{
    UNSPECIFIED,
    PROGRESSIVE,
    UPPER_FIELD_FIRST,
    LOWER_FIELD_FIRST,
};

enum class DxgiModeScaling
{
    UNSPECIFIED,
    CENTERED,
    STRETCHED,
};

enum class DxgiSwapEffect
{
    DISCARD,
    SEQUENTIAL,
    FLIP_SEQUENTIAL,
    FLIP_DISCARD,
};

enum class DxgiSwapChainFlag
{
    NONPREROTATED,
    ALLOW_MODE_SWITCH,
    GDI_COMPATIBLE,
    RESTRICTED_CONTENT,
    RESTRICT_SHARED_RESOURCE_DRIVER,
    DISPLAY_ONLY,
    FRAME_LATENCY_WAITABLE_OBJECT,
    FOREGROUND_LAYER,
    FULLSCREEN_VIDEO,
    YUV_VIDEO,
    HW_PROTECTED,
    ALLOW_TEARING,
    RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS,
};

struct STRAND_API SwapchainDesc
{

    XMINT2 WindowSize_;
    uint32_t Numerator_;
    uint32_t Denominator_;
    DxgiFormat Format_;
    DxgiModeScanlineOrder ScanlineOrdering_;
    DxgiModeScaling Scaling_;
    uint32_t SampleCount_;
    uint32_t SampleQuality_;
    DxgiBufferUsage BufferUsage_;
    uint32_t BufferCount_;
    HWND WindowHandle_;
    bool Windowed_;
    DxgiSwapEffect SwapEffect_;
    uint32_t Flags_;


};

namespace SwapchainUtils
{

static DXGI_MODE_SCANLINE_ORDER GetDxgiScanlineOrder(DxgiModeScanlineOrder scanlineOrder)
{
    switch(scanlineOrder) {
        case DxgiModeScanlineOrder::UNSPECIFIED:
            return DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        case DxgiModeScanlineOrder::PROGRESSIVE:
            return DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
        case DxgiModeScanlineOrder::UPPER_FIELD_FIRST:
            return DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
        case DxgiModeScanlineOrder::LOWER_FIELD_FIRST:
            return DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
        default:
            return DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    }
}

static DXGI_MODE_SCALING GetDxgiScaling(DxgiModeScaling scaling)
{
    switch(scaling) {
        case DxgiModeScaling::UNSPECIFIED:
            return DXGI_MODE_SCALING_UNSPECIFIED;
        case DxgiModeScaling::CENTERED:
            return DXGI_MODE_SCALING_CENTERED;
        case DxgiModeScaling::STRETCHED:
            return DXGI_MODE_SCALING_STRETCHED;
        default:
            return DXGI_MODE_SCALING_UNSPECIFIED;
    }
}

static DXGI_SWAP_EFFECT GetDxgiSwapEffect(DxgiSwapEffect swapEffect)
{
    switch(swapEffect) {
        case DxgiSwapEffect::DISCARD:
            return DXGI_SWAP_EFFECT_DISCARD;
        case DxgiSwapEffect::SEQUENTIAL:
            return DXGI_SWAP_EFFECT_SEQUENTIAL;
        case DxgiSwapEffect::FLIP_SEQUENTIAL:
            return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        case DxgiSwapEffect::FLIP_DISCARD:
            return DXGI_SWAP_EFFECT_FLIP_DISCARD;
        default:
            return DXGI_SWAP_EFFECT_DISCARD;
    }
}

static DXGI_SWAP_CHAIN_FLAG GetDxgiSwapchainFlag(DxgiSwapChainFlag flags)
{
    switch(flags) {
        case DxgiSwapChainFlag::NONPREROTATED:
            return DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
        case DxgiSwapChainFlag::ALLOW_MODE_SWITCH:
            return DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        case DxgiSwapChainFlag::GDI_COMPATIBLE:
            return DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;
        case DxgiSwapChainFlag::RESTRICTED_CONTENT:
            return DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT;
        case DxgiSwapChainFlag::RESTRICT_SHARED_RESOURCE_DRIVER:
            return DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER;
        case DxgiSwapChainFlag::DISPLAY_ONLY:
            return DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY;
        case DxgiSwapChainFlag::FRAME_LATENCY_WAITABLE_OBJECT:
            return DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        case DxgiSwapChainFlag::FOREGROUND_LAYER:
            return DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER;
        case DxgiSwapChainFlag::FULLSCREEN_VIDEO:
            return DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO;
        case DxgiSwapChainFlag::YUV_VIDEO:
            return DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO;
        case DxgiSwapChainFlag::HW_PROTECTED:
            return DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED;
        case DxgiSwapChainFlag::ALLOW_TEARING:
            return DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        case DxgiSwapChainFlag::RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS:
            return DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS;
        default:
            return DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;
    }

}

} // SwapchainUtils
} // Strand
