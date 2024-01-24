#pragma once

#include <Runtime/HAL/Device/GraphicsDeviceDesc.h>
#include <Runtime/Window/Window.h>

#include <Runtime/HAL/Swapchain/SwapchainDesc.h>

namespace Strand
{
	class GraphicsDeviceObject;
	class Swapchain;
	class Texture;
	class TextureView;
	class GraphicsBuffer;
	class Pipeline;
	class Sampler;
	class Shader;
	class CommandBuffer;
	class ResourceLayout;
	class RenderPass;

	struct TextureDesc;
	struct TextureViewDesc;
	struct GraphicsBufferDesc;
	struct GraphicsPipelineDesc;
	struct ComputePipelineDesc;
	struct SamplerDesc;
	struct ShaderDesc;
	struct CommandBufferDesc;
	struct ResourceLayoutDesc;
	struct RenderPassDesc;

	/**
	 * @class Graphics Device
	 *
	 * @brief Hardware abstraction layer for graphics device. Every graphics API
	 * should derive from this class and implement the pure virtual functions.
	 */
	class RUNTIME_API GraphicsDevice
	{
		friend class GraphicsManager;
	public:
		GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() = default;

		String GetDeviceName() { return mDeviceName; }

		NODISCARD GraphicsAPI GetGraphicsAPI() const { return mGraphicsAPI; }
		NODISCARD SharedPtr<Swapchain> GetMainSwapchain() const { return mMainSwapchain; }

		virtual void ExecuteCommandBuffers() = 0;
		virtual void ReleaseCommandBuffers() = 0;
		virtual void RecreateCommandBuffers() = 0;
	public:
		SharedPtr<Swapchain> CreateSwapchain(const SwapchainDesc& desc);
		NODISCARD SharedPtr<Texture> CreateTexture(const TextureDesc& desc);
		NODISCARD SharedPtr<TextureView> CreateTextureView(const TextureViewDesc& desc);
		NODISCARD SharedPtr<GraphicsBuffer> CreateGraphicsBuffer(const GraphicsBufferDesc& desc);
		NODISCARD SharedPtr<Pipeline> CreateGraphicsPipeline(const GraphicsPipelineDesc& desc);
		NODISCARD SharedPtr<Pipeline> CreateComputePipeline(const ComputePipelineDesc& desc);
		NODISCARD SharedPtr<Sampler> CreateSampler(const SamplerDesc& desc);
		NODISCARD SharedPtr<Shader> CreateShader(const ShaderDesc& desc);
		NODISCARD SharedPtr<CommandBuffer> CreateCommandBuffer();
		NODISCARD SharedPtr<ResourceLayout> CreateResourceLayout(const ResourceLayoutDesc& desc);
		NODISCARD SharedPtr<RenderPass> CreateRenderPass(const RenderPassDesc& desc);

		NODISCARD ArrayList<SharedPtr<CommandBuffer>>& GetCommandBuffers() { return mCommandBuffers; }

	protected:
		virtual SharedPtr<Swapchain> CreateSwapchainHAL(const SwapchainDesc& desc) = 0;
		virtual NODISCARD SharedPtr<Texture> CreateTextureHAL(const TextureDesc& desc) = 0;
		virtual NODISCARD SharedPtr<TextureView> CreateTextureViewHAL(const TextureViewDesc& desc) = 0;
		virtual NODISCARD SharedPtr<GraphicsBuffer> CreateGraphicsBufferHAL(const GraphicsBufferDesc& desc) = 0;
		virtual NODISCARD SharedPtr<Pipeline> CreateGraphicsPipelineHAL(const GraphicsPipelineDesc& desc) = 0;
		virtual NODISCARD SharedPtr<Pipeline> CreateComputePipelineHAL(const ComputePipelineDesc& desc) = 0;
		virtual NODISCARD SharedPtr<Sampler> CreateSamplerHAL(const SamplerDesc& desc) = 0;
		virtual NODISCARD SharedPtr<Shader> CreateShaderHAL(const ShaderDesc& desc) = 0;
		virtual NODISCARD SharedPtr<CommandBuffer> CreateCommandBufferHAL() = 0;
		virtual NODISCARD SharedPtr<ResourceLayout> CreateResourceLayoutHAL(const ResourceLayoutDesc& desc) = 0;
		virtual NODISCARD SharedPtr<RenderPass> CreateRenderPassHAL(const RenderPassDesc& desc) = 0;

	private:
		static SharedPtr<GraphicsDevice> CreateDevice(const GraphicsDeviceDesc& desc);

	private:
		SharedPtr<Window> mOwnedWindow;
		GraphicsAPI mGraphicsAPI;
		SharedPtr<Swapchain> mMainSwapchain;
		ArrayList<SharedPtr<GraphicsDeviceObject>> mDeviceObjects;
		String mDeviceName;

		ArrayList<SharedPtr<CommandBuffer>> mCommandBuffers;
	};
}
