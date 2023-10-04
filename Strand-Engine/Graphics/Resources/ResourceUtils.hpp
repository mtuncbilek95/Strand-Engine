// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once
namespace Strand
{

enum class ShaderResourceViewDimension
{
    UNKNOWN,
    BUFFER,
    TEXTURE1D,
    TEXTURE1D_ARRAY,
    TEXTURE2D,
    TEXTURE2D_ARRAY,
    TEXTURE2D_MULTISAMPLE,
    TEXTURE2D_MULTISAMPLE_ARRAY,
    TEXTURE3D,
    TEXTURE_CUBE,
    TEXTURE_CUBE_ARRAY,
};

enum class ResourceUsage
{
    DEFAULT,
    IMMUTABLE,
    DYNAMIC,
    STAGING
};

enum class ResourceCPUAccessFlags
{
    NONE,
    READ,
    WRITE
};

enum class ResourceBindFlags
{
    VERTEX_BUFFER,
    INDEX_BUFFER,
    CONSTANT_BUFFER,
    SHADER_RESOURCE,
    RENDER_TARGET,
    DEPTH_STENCIL
};

struct ResourceUtils
{
    static D3D11_USAGE GetResourceUsage(ResourceUsage usage)
    {
        switch(usage) {
            case ResourceUsage::DEFAULT:
                return D3D11_USAGE_DEFAULT;
            case ResourceUsage::IMMUTABLE:
                return D3D11_USAGE_IMMUTABLE;
            case ResourceUsage::DYNAMIC:
                return D3D11_USAGE_DYNAMIC;
            case ResourceUsage::STAGING:
                return D3D11_USAGE_STAGING;
            default:
                return D3D11_USAGE_DEFAULT;
        }
    }

    static D3D11_BIND_FLAG GetResourceBindFlag(ResourceBindFlags bindFlag)
    {
        switch(bindFlag) {
            case ResourceBindFlags::VERTEX_BUFFER:
                return D3D11_BIND_VERTEX_BUFFER;
            case ResourceBindFlags::INDEX_BUFFER:
                return D3D11_BIND_INDEX_BUFFER;
            case ResourceBindFlags::CONSTANT_BUFFER:
                return D3D11_BIND_CONSTANT_BUFFER;
            case ResourceBindFlags::SHADER_RESOURCE:
                return D3D11_BIND_SHADER_RESOURCE;
            case ResourceBindFlags::RENDER_TARGET:
                return D3D11_BIND_RENDER_TARGET;
            case ResourceBindFlags::DEPTH_STENCIL:
                return D3D11_BIND_DEPTH_STENCIL;
            default:
                return D3D11_BIND_VERTEX_BUFFER;
        }
    }

    static uint32_t GetResourceCPUAccessFlag(ResourceCPUAccessFlags cpuAccessFlag)
    {
        switch(cpuAccessFlag) {
            case ResourceCPUAccessFlags::NONE:
                return 0;
            case ResourceCPUAccessFlags::READ:
                return D3D11_CPU_ACCESS_READ;
            case ResourceCPUAccessFlags::WRITE:
                return D3D11_CPU_ACCESS_WRITE;
            default:
                return 0;
        }
    }

    static D3D11_SRV_DIMENSION GetResourceSRVDimension(ShaderResourceViewDimension srvDimension)
    {
        switch(srvDimension) {
            case ShaderResourceViewDimension::UNKNOWN:
                return D3D11_SRV_DIMENSION_UNKNOWN;
            case ShaderResourceViewDimension::BUFFER:
                return D3D11_SRV_DIMENSION_BUFFER;
            case ShaderResourceViewDimension::TEXTURE1D:
                return D3D11_SRV_DIMENSION_TEXTURE1D;
            case ShaderResourceViewDimension::TEXTURE1D_ARRAY:
                return D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
            case ShaderResourceViewDimension::TEXTURE2D:
                return D3D11_SRV_DIMENSION_TEXTURE2D;
            case ShaderResourceViewDimension::TEXTURE2D_ARRAY:
                return D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
            case ShaderResourceViewDimension::TEXTURE2D_MULTISAMPLE:
                return D3D11_SRV_DIMENSION_TEXTURE2DMS;
            case ShaderResourceViewDimension::TEXTURE2D_MULTISAMPLE_ARRAY:
                return D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
            case ShaderResourceViewDimension::TEXTURE3D:
                return D3D11_SRV_DIMENSION_TEXTURE3D;
            case ShaderResourceViewDimension::TEXTURE_CUBE:
                return D3D11_SRV_DIMENSION_TEXTURECUBE;
            case ShaderResourceViewDimension::TEXTURE_CUBE_ARRAY:
                return D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
            default:
                return D3D11_SRV_DIMENSION_UNKNOWN;
        }
    }

};

} // Strand
