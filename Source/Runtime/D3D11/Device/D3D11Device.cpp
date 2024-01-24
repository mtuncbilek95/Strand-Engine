#include "D3D11Device.h"

#include <Runtime/D3D11/Swapchain/D3D11Swapchain.h>

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

	NODISCARD SharedPtr<Swapchain> D3D11Device::CreateSwapchainHAL(const SwapchainDesc& desc)
	{
		SharedPtr<D3D11Swapchain> swapchain = std::make_shared<D3D11Swapchain>(desc, mD3D11Device.Get());
		return swapchain;
	}

	NODISCARD SharedPtr<Texture> D3D11Device::CreateTextureHAL(const TextureDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<TextureView> D3D11Device::CreateTextureViewHAL(const TextureViewDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<GraphicsBuffer> D3D11Device::CreateGraphicsBufferHAL(const GraphicsBufferDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<Pipeline> D3D11Device::CreateGraphicsPipelineHAL(const GraphicsPipelineDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<Pipeline> D3D11Device::CreateComputePipelineHAL(const ComputePipelineDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<Sampler> D3D11Device::CreateSamplerHAL(const SamplerDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<Shader> D3D11Device::CreateShaderHAL(const ShaderDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<CommandBuffer> D3D11Device::CreateCommandBufferHAL(const CommandBufferDesc& desc)
	{
		return nullptr;
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
