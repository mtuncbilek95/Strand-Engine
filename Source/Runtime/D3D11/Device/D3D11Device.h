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

		virtual void BindPipeline(const SharedPtr<Pipeline>& pipeline) override;
		virtual void BindVertexBuffer(const ArrayList<SharedPtr<GraphicsBuffer>>& buffers) override;
		virtual void BindIndexBuffer(const SharedPtr<GraphicsBuffer>& buffer) override;
		virtual void UpdateBuffer(const SharedPtr<GraphicsBuffer>& buffer, const void* data, uint32 size) override;
		virtual void BindResourceLayout(const SharedPtr<ResourceLayout>& resourceLayout) override;
		virtual void DrawIndexed(const uint32 indexCount, const uint32 indexOffset, const uint32 vertexOffset) override;

	protected:
		NODISCARD SharedPtr<Swapchain> CreateSwapchainHAL(const SwapchainDesc& desc) override;
		NODISCARD SharedPtr<Texture> CreateTextureHAL(const TextureDesc& desc) override;
		NODISCARD SharedPtr<TextureView> CreateTextureViewHAL(const TextureViewDesc& desc) override;
		NODISCARD SharedPtr<GraphicsBuffer> CreateGraphicsBufferHAL(const GraphicsBufferDesc& desc) override;
		NODISCARD SharedPtr<Pipeline> CreateGraphicsPipelineHAL(const GraphicsPipelineDesc& desc) override;
		NODISCARD SharedPtr<Pipeline> CreateComputePipelineHAL(const ComputePipelineDesc& desc) override;
		NODISCARD SharedPtr<Sampler> CreateSamplerHAL(const SamplerDesc& desc) override;
		NODISCARD SharedPtr<Shader> CreateShaderHAL(const ShaderDesc& desc) override;
		NODISCARD SharedPtr<ResourceLayout> CreateResourceLayoutHAL(const ResourceLayoutDesc& desc) override;

	private:
		ComPtr<ID3D11Device> mD3D11Device;
		ComPtr<ID3D11DeviceContext> mD3DImmediateContext;
	};
}
