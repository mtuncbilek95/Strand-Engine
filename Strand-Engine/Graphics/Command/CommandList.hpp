// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Graphics/GraphicsDevice/DeviceObject.hpp>
#include <Graphics/Pipeline/ShaderStage.hpp>

namespace Strand
{

class Framebuffer;
class Pipeline;
class SamplerState;
class GraphicsBuffer;
class GraphicsTextureView;

// @brief The command list class
class STRAND_API CommandList : public DeviceObject
{
public:
    explicit CommandList(std::shared_ptr<GraphicsDevice> device);
    CommandList(const CommandList&) = delete;
    CommandList& operator=(const CommandList&) = delete;
    ~CommandList() override = default;

    DXHEAP<ID3D11DeviceContext>& GetDefferedContext() { return DeferredContext_; }
    DXHEAP<ID3D11CommandList>& GetCommandList() { return CommandList_; }

    // @brief Binds the framebuffer to the command list
    void BindFramebuffer(std::shared_ptr<Framebuffer> framebuffer);
    // @brief Binds the pipeline to the command list
    void BindPipeline(std::shared_ptr<Pipeline> pipeline);
    // @brief Binds the viewport to the command list
    void BindViewport(XMINT2 windowSize);
    // @brief Binds the vertex buffer to the command list
    void BindVertexBuffer(const std::vector<std::shared_ptr<GraphicsBuffer>>& vertexBuffer);
    // @brief Binds the index buffer to the command list
    void BindIndexBuffer(std::shared_ptr<GraphicsBuffer> indexBuffer);
    // @brief Binds the resources to the command list
    void BindResources(const std::vector<std::shared_ptr<GraphicsTextureView>>& textureViews, const std::vector<std::shared_ptr<SamplerState>>& samplerStates, const std::vector<std::shared_ptr<GraphicsBuffer>>& constantBuffers, ShaderStage stage);
    // @brief Draws the indexed vertices
    void DrawIndexed(uint32_t indexCount, uint32_t startIndexLocation, int32_t baseVertexLocation);
    // @brief Clears the buffer
    void ClearBuffer(std::shared_ptr<Framebuffer> framebuffer, XMVECTOR color);
    // @brief Updates the dynamic buffer
    void UpdateDynamicBuffer(std::shared_ptr<GraphicsBuffer> buffer, const void* data, uint32_t size);
    // @brief Clears the command list
    void ClearCommandList() { CommandList_.Reset(); }

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::COMMAND; }
private:
    DXHEAP<ID3D11DeviceContext> DeferredContext_;
    DXHEAP<ID3D11CommandList> CommandList_;
};

} // strand
