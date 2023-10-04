// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "CommandList.hpp"

#include <Common/Log.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>

#include <Graphics/Framebuffer/Framebuffer.hpp>
#include <Graphics/Pipeline/Pipeline.hpp>
#include <Graphics/Resources/GraphicsBuffer/GraphicsBuffer.hpp>
#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp>
#include <Graphics/Resources/SamplerState/SamplerState.hpp>
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Pipeline/InputLayout/InputLayout.hpp>


namespace Strand
{

CommandList::CommandList(GraphicsDevice* device) : FramebufferRef_(nullptr), PipelineRef_(nullptr)
{
    GraphicsDevice_ = device;

    DX_PRINT_LOG("Create Deferred Context", device->GetDevice()->CreateDeferredContext(0, DeferredContext_.GetAddressOf()));
}

void CommandList::BindFramebuffer(Framebuffer* framebuffer)
{
    FramebufferRef_ = framebuffer;

    DeferredContext_->OMSetRenderTargets(1, framebuffer->GetColorAttachmentRTV().GetAddressOf(), framebuffer->GetDepthAttachmentDSV().Get());
}

void CommandList::BindPipeline(Pipeline* pipeline)
{
    PipelineRef_ = pipeline;

    for(auto& shader : PipelineRef_->GetDesc().Shaders_) {
        switch(shader->GetShaderType()) {
            case ShaderType::VERTEX_SHADER:
                DeferredContext_->VSSetShader(shader->GetVertexShader().Get(), nullptr, 0);
                break;
            case ShaderType::PIXEL_SHADER:
                DeferredContext_->PSSetShader(shader->GetPixelShader().Get(), nullptr, 0);
                break;
            default:
                break;
        }
    }

    DeferredContext_->IASetInputLayout(pipeline->GetInputLayout().Get());
    const float factor[4] = {0, 0, 0, 0};
    DeferredContext_->OMSetBlendState(pipeline->GetBlendState().Get(), factor, D3D11_APPEND_ALIGNED_ELEMENT);
    DeferredContext_->OMSetDepthStencilState(pipeline->GetDepthStencilState().Get(), 0);
    DeferredContext_->RSSetState(pipeline->GetRasterizerState().Get());
    DeferredContext_->IASetPrimitiveTopology(InputLayoutUtils::GetPrimitiveTopology(pipeline->GetDesc().InputAssemblerDesc_->MeshTopology_));

}

void CommandList::BindViewport(XMUINT2 windowSize)
{
    D3D11_VIEWPORT viewport{};

    viewport.TopLeftX = 0.f;
    viewport.TopLeftY = 0.f;
    viewport.Width = static_cast<float>(windowSize.x);
    viewport.Height = static_cast<float>(windowSize.y);
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.f;

    //This may need for loop in order to use with multiple viewports.
    DeferredContext_->RSSetViewports(1, &viewport);
}

void CommandList::BindVertexBuffer(GraphicsBuffer* vertexBuffer)
{
    uint32_t stride = vertexBuffer->GetDesc().StructureByteStride;
    uint32_t offset = 0;

    DeferredContext_->IASetVertexBuffers(0, 1, vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
}

void CommandList::BindIndexBuffer(GraphicsBuffer* indexBuffer)
{
    DeferredContext_->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void CommandList::BindResources(std::vector<GraphicsTextureView*> textureViews, std::vector<SamplerState*> samplerStates, std::vector<GraphicsBuffer*> constantBuffers)
{
    ID3D11ShaderResourceView* srvs[128];
    for(int i = 0; i < textureViews.size(); i++) {
        srvs[i] = textureViews[i]->GetShaderResourceView().Get();
    }

    ID3D11SamplerState* samplers[16];
    for(int i = 0; i < samplerStates.size(); i++) {
        samplers[i] = samplerStates[i]->GetSamplerState().Get();
    }

    ID3D11Buffer* cbs[16];
    for(int i = 0; i < constantBuffers.size(); i++) {
        cbs[i] = constantBuffers[i]->GetBuffer().Get();
    }

    for(int i = 0; i < PipelineRef_->GetObjectStageDesc().ShaderStages_.size(); i++) {
        switch(PipelineRef_->GetObjectStageDesc().ShaderStages_[i].Stage_) {
            case ShaderStage::VERTEX_SHADER:
                DeferredContext_->VSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->VSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->VSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            case ShaderStage::PIXEL_SHADER:
                DeferredContext_->PSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->PSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->PSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            case ShaderStage::COMPUTE_SHADER:
                DeferredContext_->CSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->CSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->CSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            case ShaderStage::GEOMETRY_SHADER:
                DeferredContext_->GSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->GSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->GSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            case ShaderStage::HULL_SHADER:
                DeferredContext_->HSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->HSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->HSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            case ShaderStage::DOMAIN_SHADER:
                DeferredContext_->DSSetShaderResources(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].TextureViewsSlotCount_, srvs);
                DeferredContext_->DSSetSamplers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].SamplerStatesSlotCount_, samplers);
                DeferredContext_->DSSetConstantBuffers(0, PipelineRef_->GetObjectStageDesc().ShaderStages_[i].ConstantBuffersSlotCount_, cbs);
                break;
            default:
                std::cerr << "Unknown Shader Stage\n";
                break;
        }
    }
}

void CommandList::DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
    DeferredContext_->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void CommandList::ClearBuffer(XMVECTOR color)
{
    DeferredContext_->ClearRenderTargetView(FramebufferRef_->GetColorAttachmentRTV().Get(), color.m128_f32);
    DeferredContext_->ClearDepthStencilView(FramebufferRef_->GetDepthAttachmentDSV().Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
}

} // Strand