// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

enum class DxgiFormat
{
    UNKNOWN,
    RGBA32_TYPELESS,
    RGBA32_FLOAT,
    RGBA32_UNSIGNED_INT,
    RGBA32_SIGNED_INT,

    RGB32_TYPELESS,
    RGB32_FLOAT,
    RGB32_UNSIGNED_INT,
    RGB32_SIGNED_INT,

    RGBA16_TYPELESS,
    RGBA16_FLOAT,
    RGBA16_UNSIGNED_NORMALIZED,
    RGBA16_UNSIGNED_INT,
    RGBA16_SIGNED_NORMALIZED,
    RGBA16_SIGNED_INT,

    RG32_TYPELESS,
    RG32_FLOAT,
    RG32_UNSIGNED_INT,
    RG32_SIGNED_INT,

    RGBA8_TYPELESS,
    RGBA8_UNSIGNED_NORMALIZED,
    RGBA8_UNSIGNED_INT,
    RGBA8_SIGNED_NORMALIZED,
    RGBA8_SIGNED_INT,

    RG16_TYPELESS,
    RG16_FLOAT,
    RG16_UNSIGNED_NORMALIZED,
    RG16_UNSIGNED_INT,
    RG16_SIGNED_NORMALIZED,
    RG16_SIGNED_INT,

    R32_TYPELESS,
    D32_FLOAT,
    R32_FLOAT,
    R32_UNSIGNED_INT,
    R32_SIGNED_INT,

    D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT,
    R24_UNSIGNED_NORMALIZED_X8_TYPELESS,

    RG8_TYPELESS,
    RG8_UNSIGNED_NORMALIZED,
    RG8_UNSIGNED_INT,
    RG8_SIGNED_NORMALIZED,
    RG8_SIGNED_INT,

    R16_TYPELESS,
    R16_FLOAT,
    D16_UNSIGNED_NORMALIZED,
    R16_UNSIGNED_NORMALIZED,
    R16_UNSIGNED_INT,
    R16_SIGNED_NORMALIZED,
    R16_SIGNED_INT,

    R8_TYPELESS,
    R8_UNSIGNED_NORMALIZED,
    R8_UNSIGNED_INT,
    R8_SIGNED_NORMALIZED,
    R8_SIGNED_INT,
    A8_UNSIGNED_NORMALIZED
};

enum class DxgiBufferUsage
{
    NONE,
    DYNAMIC,
    READ_WRITE,
    SCRATCH,
    FIELD,
    SHADER_INPUT,
    RENDER_TARGET_OUTPUT,
    BACK_BUFFER,
    SHARED,
    READ_ONLY,
    DISCARD_ON_PRESENT,
    UNORDERED_ACCESS,
};


class DxgiUtils
{
public:
    static DXGI_FORMAT GetDxgiFormat(DxgiFormat format)
    {
        switch(format) {
            case DxgiFormat::UNKNOWN:
                return DXGI_FORMAT_UNKNOWN;
            case DxgiFormat::RGBA32_TYPELESS:
                return DXGI_FORMAT_R32G32B32A32_TYPELESS;
            case DxgiFormat::RGBA32_FLOAT:
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case DxgiFormat::RGBA32_UNSIGNED_INT:
                return DXGI_FORMAT_R32G32B32A32_UINT;
            case DxgiFormat::RGBA32_SIGNED_INT:
                return DXGI_FORMAT_R32G32B32A32_SINT;
            case DxgiFormat::RGB32_TYPELESS:
                return DXGI_FORMAT_R32G32B32_TYPELESS;
            case DxgiFormat::RGB32_FLOAT:
                return DXGI_FORMAT_R32G32B32_FLOAT;
            case DxgiFormat::RGB32_UNSIGNED_INT:
                return DXGI_FORMAT_R32G32B32_UINT;
            case DxgiFormat::RGB32_SIGNED_INT:
                return DXGI_FORMAT_R32G32B32_SINT;
            case DxgiFormat::RGBA16_TYPELESS:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case DxgiFormat::RGBA16_FLOAT:
                return DXGI_FORMAT_R16G16B16A16_FLOAT;
            case DxgiFormat::RGBA16_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R16G16B16A16_UNORM;
            case DxgiFormat::RGBA16_UNSIGNED_INT:
                return DXGI_FORMAT_R16G16B16A16_UINT;
            case DxgiFormat::RGBA16_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R16G16B16A16_SNORM;
            case DxgiFormat::RGBA16_SIGNED_INT:
                return DXGI_FORMAT_R16G16B16A16_SINT;
            case DxgiFormat::RG32_TYPELESS:
                return DXGI_FORMAT_R32G32_TYPELESS;
            case DxgiFormat::RG32_FLOAT:
                return DXGI_FORMAT_R32G32_FLOAT;
            case DxgiFormat::RG32_UNSIGNED_INT:
                return DXGI_FORMAT_R32G32_UINT;
            case DxgiFormat::RG32_SIGNED_INT:
                return DXGI_FORMAT_R32G32_SINT;
            case DxgiFormat::RGBA8_TYPELESS:
                return DXGI_FORMAT_R8G8B8A8_TYPELESS;
            case DxgiFormat::RGBA8_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            case DxgiFormat::RGBA8_UNSIGNED_INT:
                return DXGI_FORMAT_R8G8B8A8_UINT;
            case DxgiFormat::RGBA8_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R8G8B8A8_SNORM;
            case DxgiFormat::RGBA8_SIGNED_INT:
                return DXGI_FORMAT_R8G8B8A8_SINT;
            case DxgiFormat::RG16_TYPELESS:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case DxgiFormat::RG16_FLOAT:
                return DXGI_FORMAT_R16G16_FLOAT;
            case DxgiFormat::RG16_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R16G16_UNORM;
            case DxgiFormat::RG16_UNSIGNED_INT:
                return DXGI_FORMAT_R16G16_UINT;
            case DxgiFormat::RG16_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R16G16_SNORM;
            case DxgiFormat::RG16_SIGNED_INT:
                return DXGI_FORMAT_R16G16_SINT;
            case DxgiFormat::R32_TYPELESS:
                return DXGI_FORMAT_R32_TYPELESS;
            case DxgiFormat::D32_FLOAT:
                return DXGI_FORMAT_D32_FLOAT;
            case DxgiFormat::R32_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case DxgiFormat::R32_UNSIGNED_INT:
                return DXGI_FORMAT_R32_UINT;
            case DxgiFormat::R32_SIGNED_INT:
                return DXGI_FORMAT_R32_SINT;
            case DxgiFormat::D24_UNSIGNED_NORMALIZED_S8_UNSIGNED_INT:
                return DXGI_FORMAT_D24_UNORM_S8_UINT;
            case DxgiFormat::R24_UNSIGNED_NORMALIZED_X8_TYPELESS:
                return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            case DxgiFormat::RG8_TYPELESS:
                return DXGI_FORMAT_R8G8_TYPELESS;
            case DxgiFormat::RG8_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R8G8_UNORM;
            case DxgiFormat::RG8_UNSIGNED_INT:
                return DXGI_FORMAT_R8G8_UINT;
            case DxgiFormat::RG8_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R8G8_SNORM;
            case DxgiFormat::RG8_SIGNED_INT:
                return DXGI_FORMAT_R8G8_SINT;
            case DxgiFormat::R16_TYPELESS:
                return DXGI_FORMAT_R16_TYPELESS;
            case DxgiFormat::R16_FLOAT:
                return DXGI_FORMAT_R16_FLOAT;
            case DxgiFormat::D16_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_D16_UNORM;
            case DxgiFormat::R16_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R16_UNORM;
            case DxgiFormat::R16_UNSIGNED_INT:
                return DXGI_FORMAT_R16_UINT;
            case DxgiFormat::R16_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R16_SNORM;
            case DxgiFormat::R16_SIGNED_INT:
                return DXGI_FORMAT_R16_SINT;
            case DxgiFormat::R8_TYPELESS:
                return DXGI_FORMAT_R8_TYPELESS;
            case DxgiFormat::R8_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_R8_UNORM;
            case DxgiFormat::R8_UNSIGNED_INT:
                return DXGI_FORMAT_R8_UINT;
            case DxgiFormat::R8_SIGNED_NORMALIZED:
                return DXGI_FORMAT_R8_SNORM;
            case DxgiFormat::R8_SIGNED_INT:
                return DXGI_FORMAT_R8_SINT;
            case DxgiFormat::A8_UNSIGNED_NORMALIZED:
                return DXGI_FORMAT_A8_UNORM;
            default:
                return DXGI_FORMAT_UNKNOWN;
        }
    }

    static uint32_t GetDxgiUsage(DxgiBufferUsage bufferUsage)
    {
        switch(bufferUsage) {
            case DxgiBufferUsage::NONE:
                return DXGI_CPU_ACCESS_NONE;
            case DxgiBufferUsage::DYNAMIC:
                return DXGI_CPU_ACCESS_DYNAMIC;
            case DxgiBufferUsage::READ_WRITE:
                return DXGI_CPU_ACCESS_READ_WRITE;
            case DxgiBufferUsage::SCRATCH:
                return DXGI_CPU_ACCESS_SCRATCH;
            case DxgiBufferUsage::FIELD:
                return DXGI_CPU_ACCESS_FIELD;
            case DxgiBufferUsage::SHADER_INPUT:
                return DXGI_USAGE_SHADER_INPUT;
            case DxgiBufferUsage::RENDER_TARGET_OUTPUT:
                return DXGI_USAGE_RENDER_TARGET_OUTPUT;
            case DxgiBufferUsage::BACK_BUFFER:
                return DXGI_USAGE_BACK_BUFFER;
            case DxgiBufferUsage::SHARED:
                return DXGI_USAGE_SHARED;
            case DxgiBufferUsage::READ_ONLY:
                return DXGI_USAGE_READ_ONLY;
            case DxgiBufferUsage::DISCARD_ON_PRESENT:
                return DXGI_USAGE_DISCARD_ON_PRESENT;
            case DxgiBufferUsage::UNORDERED_ACCESS:
                return DXGI_USAGE_UNORDERED_ACCESS;
            default:
                return DXGI_CPU_ACCESS_NONE;
        }
    }
};

} // Strand
