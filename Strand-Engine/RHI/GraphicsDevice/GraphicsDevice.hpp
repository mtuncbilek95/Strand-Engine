// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Core.hpp>

#include <RHI/Common/GraphicsApi.hpp>
#include <Containers/ArrayList.hpp>
#include <RHI/GraphicsDevice/GraphicsDeviceDesc.hpp>

namespace Strand
{

class DeviceObject;
class Swapchain;
class Framebuffer;
class Shader;
class Command;

class Pipeline;

class GraphicsBuffer;
class GraphicsTexture;
class GraphicsSampler;
class GraphicsResource;

struct SwapchainDesc;
struct FramebufferDesc;
struct ShaderDesc;

struct GraphicsPipelineDesc;

struct GraphicsBufferDesc;
struct GraphicsTextureDesc;
struct GraphicsSamplerDesc;
struct GraphicsResourceDesc;


/* @brief This is the main RHI device. This device will be used to create all other RHI objects. Eventually, graphics
 * api will be abstracted and this class will be the main interface to the graphics api. User will use this class to initialize the engine.
 */
class ENGINE_API GraphicsDevice
{
public:
    GraphicsDevice(const GraphicsDeviceDesc& desc);
    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice(GraphicsDevice&&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(GraphicsDevice&&) = delete;
    ~GraphicsDevice() = default;

    static GraphicsDevice* CreateGraphicsDevice(const GraphicsDeviceDesc& desc);

    // Swapchain function to be used by the user.
    NODISCARD Swapchain* CreateSwapchain(const SwapchainDesc& desc);
    // Framebuffer function to be used by the user.
    NODISCARD Framebuffer* CreateFramebuffer(const FramebufferDesc& desc);
    // Shader function to be used by the user.
    NODISCARD Shader* CreateShader(const ShaderDesc& desc);
    // Command function to be used by the user.
    NODISCARD Command* CreateCommand();

    // Pipeline function to be used by the user.
    NODISCARD Pipeline* CreateGraphicsPipeline(const GraphicsPipelineDesc& desc);
    // GraphicsBuffer function to be used by the user.
    NODISCARD GraphicsBuffer* CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
    // GraphicsTexture function to be used by the user.
    NODISCARD GraphicsTexture* CreateGraphicsTexture(const GraphicsTextureDesc& desc);
    // GraphicsSampler function to be used by the user.
    NODISCARD GraphicsSampler* CreateGraphicsSampler(const GraphicsSamplerDesc& desc);
    // GraphicsResource function to be used by the user.
    NODISCARD GraphicsResource* CreateGraphicsResource(const GraphicsResourceDesc& desc);

    void RegisterCommand(ArrayList<Command*> commandLists);
    void SwapchainPresent();

protected:
    // Swapchain function to be implemented by the graphics api.
    NODISCARD virtual Swapchain* CreateSwapchainRHI(const SwapchainDesc& desc) = 0;
    // Framebuffer function to be implemented by the graphics api.
    NODISCARD virtual Framebuffer* CreateFramebufferRHI(const FramebufferDesc& desc) = 0;
    // Pipeline function to be implemented by the graphics api.
    NODISCARD virtual Pipeline* CreatePipelineRHI(const GraphicsPipelineDesc& desc) = 0;
    // Shader function to be implemented by the graphics api.
    NODISCARD virtual Shader* CreateShaderRHI(const ShaderDesc& desc) = 0;
    // Command function to be implemented by the graphics api.
    NODISCARD virtual Command* CreateCommandRHI() = 0;

    // GraphicsBuffer function to be implemented by the graphics api.
    NODISCARD virtual GraphicsBuffer* CreateGraphicsBufferRHI(const GraphicsBufferDesc& desc) = 0;
    // GraphicsTexture function to be implemented by the graphics api.
    NODISCARD virtual GraphicsTexture* CreateGraphicsTextureRHI(const GraphicsTextureDesc& desc) = 0;
    // GraphicsSampler function to be implemented by the graphics api.
    NODISCARD virtual GraphicsSampler* CreateGraphicsSamplerRHI(const GraphicsSamplerDesc& desc) = 0;
    // GraphicsResource function to be implemented by the graphics api.
    NODISCARD virtual GraphicsResource* CreateGraphicsResourceRHI(const GraphicsResourceDesc& desc) = 0;

    FORCEINLINE virtual GraphicsApi GetGraphicsApi() = 0;
    virtual void RegisterCommandRHI(ArrayList<Command*> commandList) = 0;
    virtual void SwapchainPresentRHI() = 0;

    void RegisterDeviceObject(DeviceObject* deviceObject);

private:
    ArrayList<DeviceObject*> DeviceObjects_;
    Swapchain* Swapchain_;

    GraphicsDeviceDesc Desc_;
};

} // Strand
