#pragma once

#include <Runtime/HAL/Device/GraphicsDevice.h>

#include <d3d11_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11Device : public GraphicsDevice
	{
	public:
		D3D11Device(const GraphicsDeviceDesc& desc);
		~D3D11Device() override = default;

		const ComPtr<ID3D11Device>& GetD3D11Device() { return mD3D11Device; }
		const ComPtr<ID3D11DeviceContext>& GetD3DImmediateContext() { return mD3DImmediateContext; }

		void ExecuteCommandBuffers() override;
		void ReleaseCommandBuffers() override;
		void RecreateCommandBuffers() override;

	protected:
		NODISCARD SharedPtr<Swapchain> CreateSwapchainHAL(const SwapchainDesc& desc) override;
		NODISCARD SharedPtr<Texture> CreateTextureHAL(const TextureDesc& desc) override;
		NODISCARD SharedPtr<TextureView> CreateTextureViewHAL(const TextureViewDesc& desc) override;
		NODISCARD SharedPtr<GraphicsBuffer> CreateGraphicsBufferHAL(const GraphicsBufferDesc& desc) override;
		NODISCARD SharedPtr<Pipeline> CreateGraphicsPipelineHAL(const GraphicsPipelineDesc& desc) override;
		NODISCARD SharedPtr<Pipeline> CreateComputePipelineHAL(const ComputePipelineDesc& desc) override;
		NODISCARD SharedPtr<Sampler> CreateSamplerHAL(const SamplerDesc& desc) override;
		NODISCARD SharedPtr<Shader> CreateShaderHAL(const ShaderDesc& desc) override;
		NODISCARD SharedPtr<CommandBuffer> CreateCommandBufferHAL() override;
		NODISCARD SharedPtr<ResourceLayout> CreateResourceLayoutHAL(const ResourceLayoutDesc& desc) override;
		NODISCARD SharedPtr<RenderPass> CreateRenderPassHAL(const RenderPassDesc& desc) override;

	private:
		ComPtr<ID3D11Device> mD3D11Device;
		ComPtr<ID3D11DeviceContext> mD3DImmediateContext;
	};
}
