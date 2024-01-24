#include "D3D11Device.h"

#include <Runtime/D3D11/Swapchain/D3D11Swapchain.h>
#include <Runtime/D3D11/Texture/D3D11Texture.h>
#include <Runtime/D3D11/Texture/D3D11TextureView.h>
#include <Runtime/D3D11/Buffer/D3D11GraphicsBuffer.h>
#include <Runtime/D3D11/Pipeline/D3D11Pipeline.h>
#include <Runtime/D3D11/Sampler/D3D11Sampler.h>
#include <Runtime/D3D11/Shader/D3D11Shader.h>
#include <Runtime/D3D11/Command/D3D11CommandBuffer.h>

namespace Strand
{
	D3D11Device::D3D11Device(const GraphicsDeviceDesc& desc) : GraphicsDevice(desc)
	{
		D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

#ifdef STRAND_DEBUG
		uint32 deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
		uint32 deviceFlags = 0;
#endif

		DEV_ASSERT(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, deviceFlags, featureLevel, 1, D3D11_SDK_VERSION, mD3D11Device.GetAddressOf(), nullptr, mD3DImmediateContext.GetAddressOf())), "D3D11Device",
			"Failed to create D3D11 Device and Immediate Context");

		DEV_LOG(SE_VERBOSE, "Created D3D11 Device and Immediate Context");
	}

	void D3D11Device::ExecuteCommandBuffers()
	{
		for (auto& commandBuffer : GetCommandBuffers())
		{
			commandBuffer->Reset();
			mD3DImmediateContext->ExecuteCommandList(static_cast<D3D11CommandBuffer*>(commandBuffer.get())->GetCommandList().Get(), false);
		}
	}

	void D3D11Device::ReleaseCommandBuffers()
	{
		for (auto& commandBuffer : GetCommandBuffers())
		{
			static_cast<D3D11CommandBuffer*>(commandBuffer.get())->GetCommandList()->Release();
			static_cast<D3D11CommandBuffer*>(commandBuffer.get())->GetDeferredContext()->Release();
		}
		mD3DImmediateContext->ClearState();
	}

	void D3D11Device::RecreateCommandBuffers()
	{
		for (auto& commandBuffer : GetCommandBuffers())
		{
			static_cast<D3D11CommandBuffer*>(commandBuffer.get())->InitContext(mD3D11Device.Get());
		}
	}

	NODISCARD SharedPtr<Swapchain> D3D11Device::CreateSwapchainHAL(const SwapchainDesc& desc)
	{
		SharedPtr<D3D11Swapchain> swapchain = std::make_shared<D3D11Swapchain>(desc, mD3D11Device.Get());
		return swapchain;
	}

	NODISCARD SharedPtr<Texture> D3D11Device::CreateTextureHAL(const TextureDesc& desc)
	{
		SharedPtr<D3D11Texture> texture = std::make_shared<D3D11Texture>(desc, mD3D11Device.Get());
		return texture;
	}

	NODISCARD SharedPtr<TextureView> D3D11Device::CreateTextureViewHAL(const TextureViewDesc& desc)
	{
		SharedPtr<D3D11TextureView> textureView = std::make_shared<D3D11TextureView>(desc, mD3D11Device.Get());
		return textureView;
	}

	NODISCARD SharedPtr<GraphicsBuffer> D3D11Device::CreateGraphicsBufferHAL(const GraphicsBufferDesc& desc)
	{
		SharedPtr<D3D11GraphicsBuffer> graphicsBuffer = std::make_shared<D3D11GraphicsBuffer>(desc, mD3D11Device.Get());
		return graphicsBuffer;
	}

	NODISCARD SharedPtr<Pipeline> D3D11Device::CreateGraphicsPipelineHAL(const GraphicsPipelineDesc& desc)
	{
		SharedPtr<D3D11Pipeline> pipeline = std::make_shared<D3D11Pipeline>(desc, mD3D11Device.Get());
		return pipeline;
	}

	NODISCARD SharedPtr<Pipeline> D3D11Device::CreateComputePipelineHAL(const ComputePipelineDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<Sampler> D3D11Device::CreateSamplerHAL(const SamplerDesc& desc)
	{
		SharedPtr<D3D11Sampler> sampler = std::make_shared<D3D11Sampler>(desc, mD3D11Device.Get());
		return sampler;
	}

	NODISCARD SharedPtr<Shader> D3D11Device::CreateShaderHAL(const ShaderDesc& desc)
	{
		SharedPtr<D3D11Shader> shader = std::make_shared<D3D11Shader>(desc, mD3D11Device.Get());
		return shader;
	}

	NODISCARD SharedPtr<CommandBuffer> D3D11Device::CreateCommandBufferHAL()
	{
		SharedPtr<D3D11CommandBuffer> commandBuffer = std::make_shared<D3D11CommandBuffer>(mD3D11Device.Get());
		return commandBuffer;
	}

	NODISCARD SharedPtr<ResourceLayout> D3D11Device::CreateResourceLayoutHAL(const ResourceLayoutDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<RenderPass> D3D11Device::CreateRenderPassHAL(const RenderPassDesc& desc)
	{
		return nullptr;
	}
}
