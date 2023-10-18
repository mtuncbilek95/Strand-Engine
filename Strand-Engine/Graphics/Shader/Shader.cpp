// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Shader.hpp"

#include <Common/Log.hpp>
#include <Common/Common.hpp>
#include <FileReader/FileReader.hpp>

#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

namespace Strand
{
Shader::Shader(std::shared_ptr<GraphicsDevice> graphicsDevice, const ShaderDesc& desc)
{
    GraphicsDevice_ = graphicsDevice;
    Desc_ = desc;

    DXHEAP<ID3DBlob> errorBlob;

    std::string shaderBlob;
    std::string shaderModel;

    switch(Desc_.Type_) {
        case ShaderType::VERTEX_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("VertexShader");
            shaderModel = "vs_5_0";
            break;
        case ShaderType::PIXEL_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("PixelShader");
            shaderModel = "ps_5_0";
            break;
        case ShaderType::DOMAIN_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("DomainShader");
            shaderModel = "ds_5_0";
            break;
        case ShaderType::GEOMETRY_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("GeometryShader");
            shaderModel = "gs_5_0";
            break;
        case ShaderType::HULL_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("HullShader");
            shaderModel = "hs_5_0";
            break;
        case ShaderType::COMPUTE_SHADER:
            shaderBlob = FileReader::GetShaderNearExe("ComputeShader");
            shaderModel = "cs_5_0";
            break;
        default:
            std::cerr << "Shader type not supported" << std::endl;
            break;
    }

    DX_PRINT_LOG("Compile Shader", D3DCompile(shaderBlob.data(), shaderBlob.length(), nullptr, nullptr, nullptr, Desc_.EntryPoint_.c_str(), shaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, Blob_.GetAddressOf(), &errorBlob));

    if(errorBlob.Get() != nullptr && errorBlob.Get()->GetBufferPointer() != nullptr) {
        std::cerr <<  static_cast<char*>(errorBlob->GetBufferPointer()) << std::endl;
    }

    switch(Desc_.Type_) {
        case ShaderType::VERTEX_SHADER:
            DX_PRINT_LOG("Create Vertex Shader", GraphicsDevice_->GetDevice()->CreateVertexShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, VertexShader_.GetAddressOf()));
            break;
        case ShaderType::PIXEL_SHADER:
            DX_PRINT_LOG("Create Pixel Shader", GraphicsDevice_->GetDevice()->CreatePixelShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, PixelShader_.GetAddressOf()));
            break;
        case ShaderType::GEOMETRY_SHADER:
            DX_PRINT_LOG("Create Geometry Shader", GraphicsDevice_->GetDevice()->CreateGeometryShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, GeometryShader_.GetAddressOf()));
            break;
        case ShaderType::HULL_SHADER:
            DX_PRINT_LOG("Create Hull Shader", GraphicsDevice_->GetDevice()->CreateHullShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, HullShader_.GetAddressOf()));
            break;
        case ShaderType::DOMAIN_SHADER:
            DX_PRINT_LOG("Create Domain Shader", GraphicsDevice_->GetDevice()->CreateDomainShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, DomainShader_.GetAddressOf()));
            break;
        case ShaderType::COMPUTE_SHADER:
            DX_PRINT_LOG("Create Compute Shader", GraphicsDevice_->GetDevice()->CreateComputeShader(Blob_->GetBufferPointer(), Blob_->GetBufferSize(), nullptr, ComputeShader_.GetAddressOf()));
            break;
        default:
            std::cerr << "Shader type not supported" << std::endl;
            break;
    }
}

} // Strand