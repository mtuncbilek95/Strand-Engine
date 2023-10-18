// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Pipeline.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Pipeline/InputLayout/InputLayout.hpp>
#include <Graphics/Pipeline/DepthStencil/DepthStencil.hpp>
#include <Graphics/Pipeline/Rasterizer/Rasterizer.hpp>
#include <Graphics/Pipeline/Blend/Blend.hpp>
#include <Graphics/Resources/SamplerState/SamplerState.hpp>

namespace Strand
{

Pipeline::Pipeline(std::shared_ptr<GraphicsDevice> device, const PipelineDesc& desc)
{
    GraphicsDevice_ = device;
    Desc_ = desc;
    SamplerState_ = desc.SamplerStateDesc_->GetSamplerState();

    std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDesc;

    for(int i = 0; i < Desc_.InputAssemblerDesc_.SemanticName_.size(); i++)
    {
        D3D11_INPUT_ELEMENT_DESC inputElementDesc{};

        switch(Desc_.InputAssemblerDesc_.SemanticName_[i]) {
            case InputLayoutSemanticName::POSITION:
                inputElementDesc.SemanticName = "POSITION";
                inputElementDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            case InputLayoutSemanticName::NORMAL:
                inputElementDesc.SemanticName = "NORMAL";
                inputElementDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            case InputLayoutSemanticName::TANGENT:
                inputElementDesc.SemanticName = "TANGENT";
                inputElementDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            case InputLayoutSemanticName::BINORMAL:
                inputElementDesc.SemanticName = "BINORMAL";
                inputElementDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            case InputLayoutSemanticName::TEXCOORD:
                inputElementDesc.SemanticName = "TEXCOORD";
                inputElementDesc.Format = DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            case InputLayoutSemanticName::COLOR:
                inputElementDesc.SemanticName = "COLOR";
                inputElementDesc.Format =DxgiUtils::GetDxgiFormat(Desc_.InputAssemblerDesc_.InputFormat[i]);
                break;
            default:
                break;
        }

        inputElementDesc.SemanticIndex = Desc_.InputAssemblerDesc_.SemanticIndex_[i];
        inputElementDesc.InputSlot = Desc_.InputAssemblerDesc_.InputSlot_[i];
        inputElementDesc.AlignedByteOffset = Desc_.InputAssemblerDesc_.AlignedByteOffset_[i];
        inputElementDesc.InputSlotClass = InputLayoutUtils::GetInputClassification(Desc_.InputAssemblerDesc_.InputSlotClass_[i]);
        inputElementDesc.InstanceDataStepRate = Desc_.InputAssemblerDesc_.InstanceDataStepRate_[i];

        InputElementDesc.push_back(inputElementDesc);
    }

    for(auto & Shader : Desc_.Shaders_)
        if(Shader->GetShaderType() == ShaderType::VERTEX_SHADER)
            DX_PRINT_LOG("Create Pipeline", GraphicsDevice_->GetDevice()->CreateInputLayout(InputElementDesc.data(), InputElementDesc.size(),
                                                                                        Shader->GetShaderBlob()->GetBufferPointer(), Shader->GetShaderBlob()->GetBufferSize(),
                                                                                        &InputLayout_));

    CreateDepthStencilState();
    CreateRasterizerState();
    CreateBlendState();
}

std::shared_ptr<Shader> Pipeline::GetShader(ShaderType stage)
{
    for(auto & Shader : Desc_.Shaders_)
        if(Shader->GetShaderType() == stage)
            return Shader;
    return nullptr;
}

void Pipeline::CreateDepthStencilState()
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc{
            .DepthEnable = Desc_.DepthStencilStateDesc_.DepthEnable,
            .DepthWriteMask = DepthStencilUtils::GetDepthWriteMask(Desc_.DepthStencilStateDesc_.DepthWriteMask),
            .DepthFunc = DepthStencilUtils::GetComparisonFunc(Desc_.DepthStencilStateDesc_.DepthFunc),
            .StencilEnable = Desc_.DepthStencilStateDesc_.StencilEnable,
            .StencilReadMask = Desc_.DepthStencilStateDesc_.StencilReadMask,
            .StencilWriteMask = Desc_.DepthStencilStateDesc_.StencilWriteMask,
    };

    DX_PRINT_LOG("Create DepthStencilState", GraphicsDevice_->GetDevice()->CreateDepthStencilState(&depthStencilDesc, DepthState_.GetAddressOf()));
}

void Pipeline::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC rasterizerDesc{
            .FillMode = RasterizerStateUtils::GetFillMode(Desc_.RasterizerStateDesc_.FillMode_),
            .CullMode = RasterizerStateUtils::GetCullMode(Desc_.RasterizerStateDesc_.CullMode_),
            .FrontCounterClockwise = RasterizerStateUtils::GetFrontFace(Desc_.RasterizerStateDesc_.FrontFace_),
            .DepthBias = Desc_.RasterizerStateDesc_.DepthBias_,
            .DepthBiasClamp = Desc_.RasterizerStateDesc_.DepthBiasClamp_,
            .DepthClipEnable = Desc_.RasterizerStateDesc_.DepthClipEnable_,
            .AntialiasedLineEnable = Desc_.RasterizerStateDesc_.AntialiasedLineEnable_
    };

    DX_PRINT_LOG("Create RasterizerState", GraphicsDevice_->GetDevice()->CreateRasterizerState(&rasterizerDesc, RasterizerState_.GetAddressOf()));
}

void Pipeline::CreateBlendState()
{
    D3D11_RENDER_TARGET_BLEND_DESC rtvBlendDesc{
            .BlendEnable = Desc_.BlendStateDesc_.RenderTargetDesc.BlendEnable,
            .SrcBlend = BlendUtil::GetBlendType(Desc_.BlendStateDesc_.RenderTargetDesc.SrcBlend),
            .DestBlend = BlendUtil::GetBlendType(Desc_.BlendStateDesc_.RenderTargetDesc.DestBlend),
            .BlendOp = BlendUtil::GetBlendOp(Desc_.BlendStateDesc_.RenderTargetDesc.BlendOp),
            .SrcBlendAlpha = BlendUtil::GetBlendType(Desc_.BlendStateDesc_.RenderTargetDesc.SrcBlendAlpha),
            .DestBlendAlpha = BlendUtil::GetBlendType(Desc_.BlendStateDesc_.RenderTargetDesc.DestBlendAlpha),
            .BlendOpAlpha = BlendUtil::GetBlendOp(Desc_.BlendStateDesc_.RenderTargetDesc.BlendOpAlpha),
            .RenderTargetWriteMask = static_cast<uint8_t>(Desc_.BlendStateDesc_.RenderTargetDesc.RenderTargetWriteMask)
    };

    D3D11_BLEND_DESC blendDesc{
            .AlphaToCoverageEnable = Desc_.BlendStateDesc_.AlphaToCoverageEnable,
            .IndependentBlendEnable = Desc_.BlendStateDesc_.IndependentBlendEnable,
            .RenderTarget = {rtvBlendDesc}
    };

    DX_PRINT_LOG("Create BlendState", GraphicsDevice_->GetDevice()->CreateBlendState(&blendDesc, BlendState_.GetAddressOf()));
}


} // Strand