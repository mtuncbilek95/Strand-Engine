// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Shader/ShaderDesc.hpp>

namespace Strand
{

class STRAND_API Shader : public DeviceObject
{
public:
    Shader(GraphicsDevice* graphicsDevice, const ShaderDesc& desc);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader() override = default;

    DXHEAP<ID3D11VertexShader>& GetVertexShader() { return VertexShader_; }
    DXHEAP<ID3D11PixelShader>& GetPixelShader() { return PixelShader_; }
    DXHEAP<ID3D11DomainShader>& GetDomainShader() { return DomainShader_; }
    DXHEAP<ID3D11HullShader>& GetHullShader() { return HullShader_; }
    DXHEAP<ID3D11GeometryShader>& GetGeometryShader() { return GeometryShader_; }
    DXHEAP<ID3D11ComputeShader>& GetComputeShader() { return ComputeShader_; }
    DXHEAP<ID3DBlob>& GetShaderBlob() { return Blob_; }

    [[nodiscard]] ShaderType GetShaderType() const { return Desc_.Type_; }
    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::SHADER; }

private:
    DXHEAP<ID3D11VertexShader> VertexShader_;
    DXHEAP<ID3D11DomainShader> DomainShader_;
    DXHEAP<ID3D11HullShader> HullShader_;
    DXHEAP<ID3D11GeometryShader> GeometryShader_;
    DXHEAP<ID3D11ComputeShader> ComputeShader_;
    DXHEAP<ID3D11PixelShader> PixelShader_;

    DXHEAP<ID3DBlob> Blob_;

    ShaderDesc Desc_;
};

} // Strand
