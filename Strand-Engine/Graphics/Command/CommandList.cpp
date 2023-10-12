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

CommandList::CommandList(GraphicsDevice* device)
{
    GraphicsDevice_ = device;

    DX_PRINT_LOG("Create Deferred Context", device->GetDevice()->CreateDeferredContext(0, DeferredContext_.GetAddressOf()));
}

void CommandList::BindFramebuffer(Framebuffer* framebuffer)
{
    DeferredContext_->OMSetRenderTargets(1, framebuffer->GetColorAttachmentRTV().GetAddressOf(), framebuffer->GetDepthAttachmentDSV().Get());
}

void CommandList::BindPipeline(Pipeline* pipeline)
{
    for(auto& shader: pipeline->GetDesc().Shaders_) {
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
    DeferredContext_->IASetPrimitiveTopology(InputLayoutUtils::GetPrimitiveTopology(pipeline->GetDesc().InputAssemblerDesc_.MeshTopology_));

}

void CommandList::BindViewport(XMINT2 windowSize)
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

void CommandList::BindVertexBuffer(std::vector<GraphicsBuffer*> vertexBuffer)
{
    for(uint32_t i = 0; i < vertexBuffer.size(); ++i) {
        uint32_t stride = vertexBuffer[i]->GetDesc().StructureByteStride;
        uint32_t offset = 0;
        DeferredContext_->IASetVertexBuffers(i, 1, vertexBuffer[i]->GetBuffer().GetAddressOf(), &stride, &offset);
    }
}

void CommandList::BindIndexBuffer(GraphicsBuffer* indexBuffer)
{
    DeferredContext_->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
}

void CommandList::BindResources(const std::vector<GraphicsTextureView*>& textureViews, const std::vector<SamplerState*>& samplerStates, const std::vector<GraphicsBuffer*>& constantBuffers, ShaderStage stage)
{
    ID3D11ShaderResourceView* srvs[16] = {};
    ID3D11SamplerState* samplers[16] = {};
    ID3D11Buffer* buffers[16] = {};

    for(uint32_t i = 0; i < textureViews.size(); ++i) {
        srvs[i] = textureViews[i]->GetShaderResourceView().Get();
    }

    for(uint32_t i = 0; i < samplerStates.size(); ++i) {
        samplers[i] = samplerStates[i]->GetSamplerState().Get();
    }

    for(uint32_t i = 0; i < constantBuffers.size(); ++i) {
        buffers[i] = constantBuffers[i]->GetBuffer().Get();
    }

    switch(stage) {
        case ShaderStage::VERTEX_SHADER:
            DeferredContext_->VSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->VSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->VSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        case ShaderStage::PIXEL_SHADER:
            DeferredContext_->PSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->PSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->PSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        case ShaderStage::DOMAIN_SHADER:
            DeferredContext_->DSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->DSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->DSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        case ShaderStage::HULL_SHADER:
            DeferredContext_->HSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->HSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->HSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        case ShaderStage::GEOMETRY_SHADER:
            DeferredContext_->GSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->GSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->GSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        case ShaderStage::COMPUTE_SHADER:
            DeferredContext_->CSSetShaderResources(0, textureViews.size(), srvs);
            DeferredContext_->CSSetSamplers(0, samplerStates.size(), samplers);
            DeferredContext_->CSSetConstantBuffers(0, constantBuffers.size(), buffers);
            break;
        default:
            std::cerr << "Invalid shader stage" << std::endl;
            break;
    }

}

void CommandList::DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
    DeferredContext_->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void CommandList::ClearBuffer(Framebuffer* framebuffer, XMVECTOR color)
{
    DeferredContext_->ClearRenderTargetView(framebuffer->GetColorAttachmentRTV().Get(), color.m128_f32);
    DeferredContext_->ClearDepthStencilView(framebuffer->GetDepthAttachmentDSV().Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
}

void CommandList::UpdateDynamicBuffer(GraphicsBuffer* buffer, const void* data, uint32_t size)
{
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    DeferredContext_->Map(buffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
    memcpy(mappedSubresource.pData, data, size);
    DeferredContext_->Unmap(buffer->GetBuffer().Get(), 0);


}

} // Strand