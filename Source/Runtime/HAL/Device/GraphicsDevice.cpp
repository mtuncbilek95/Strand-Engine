#include "GraphicsDevice.h"

#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/D3D11/Device/D3D11Device.h>

#include <Runtime/HAL/Swapchain/Swapchain.h>
#include <Runtime/HAL/Texture/Texture.h>
#include <Runtime/HAL/Texture/TextureView.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>
#include <Runtime/HAL/Pipeline/Pipeline.h>
#include <Runtime/HAL/Sampler/Sampler.h>
#include <Runtime/HAL/Shader/Shader.h>
#include <Runtime/HAL/Command/CommandBuffer.h>

namespace Strand
{
	SharedPtr<GraphicsDevice> GraphicsDevice::CreateDevice(const GraphicsDeviceDesc& desc)
	{
		SharedPtr<GraphicsDevice> pDevice;

		switch (desc.UsedAPI)
		{
		case GraphicsAPI::D3D11:
		{
			pDevice = std::make_shared<D3D11Device>(desc);
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			break;
		}
		default:
			break;
		}

		DEV_ASSERT(pDevice != nullptr, "GraphicsDevice", "Failed to create graphics device");

		return pDevice;
	}

	GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc) : mGraphicsAPI(desc.UsedAPI), mOwnedWindow(desc.pWindow)
	{
		DEV_ASSERT(mOwnedWindow != nullptr, "GraphicsDevice", "Window is nullptr");
	}

	SharedPtr<Swapchain> GraphicsDevice::CreateSwapchain(const SwapchainDesc& desc)
	{
		if (mMainSwapchain != nullptr)
		{
			DEV_ASSERT(false, "GraphicsDevice", "Swapchain has already been created");
			return mMainSwapchain;
		}
		else
		{
			SharedPtr<Swapchain> pSwapchain = CreateSwapchainHAL(desc);
			DEV_ASSERT(pSwapchain != nullptr, "GraphicsDevice", "Failed to create swapchain");
			mMainSwapchain = pSwapchain;
			mMainSwapchain->_SetOwnerDevice(this);
			mDeviceObjects.push_back(pSwapchain);
			return pSwapchain;
		}
	}

	NODISCARD SharedPtr<Texture> GraphicsDevice::CreateTexture(const TextureDesc& desc)
	{
		SharedPtr<Texture> pTexture = CreateTextureHAL(desc);
		DEV_ASSERT(pTexture != nullptr, "GraphicsDevice", "Failed to create texture");
		pTexture->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pTexture);
		return pTexture;
	}

	NODISCARD SharedPtr<TextureView> GraphicsDevice::CreateTextureView(const TextureViewDesc& desc)
	{
		SharedPtr<TextureView> pTextureView = CreateTextureViewHAL(desc);
		DEV_ASSERT(pTextureView != nullptr, "GraphicsDevice", "Failed to create texture view");
		pTextureView->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pTextureView);
		return pTextureView;
	}

	NODISCARD SharedPtr<GraphicsBuffer> GraphicsDevice::CreateGraphicsBuffer(const GraphicsBufferDesc& desc)
	{
		SharedPtr<GraphicsBuffer> pBuffer = CreateGraphicsBufferHAL(desc);
		DEV_ASSERT(pBuffer != nullptr, "GraphicsDevice", "Failed to create graphics buffer");
		pBuffer->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pBuffer);
		return pBuffer;
	}

	NODISCARD SharedPtr<Pipeline> GraphicsDevice::CreateGraphicsPipeline(const GraphicsPipelineDesc& desc)
	{
		SharedPtr<Pipeline> pPipeline = CreateGraphicsPipelineHAL(desc);
		DEV_ASSERT(pPipeline != nullptr, "GraphicsDevice", "Failed to create graphics pipeline");
		pPipeline->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pPipeline);
		return pPipeline;
	}

	NODISCARD SharedPtr<Pipeline> GraphicsDevice::CreateComputePipeline(const ComputePipelineDesc& desc)
	{
		SharedPtr<Pipeline> pPipeline = CreateComputePipelineHAL(desc);
		DEV_ASSERT(pPipeline != nullptr, "GraphicsDevice", "Failed to create compute pipeline");
		pPipeline->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pPipeline);
		return pPipeline;
	}

	NODISCARD SharedPtr<Sampler> GraphicsDevice::CreateSampler(const SamplerDesc& desc)
	{
		SharedPtr<Sampler> pSampler = CreateSamplerHAL(desc);
		DEV_ASSERT(pSampler != nullptr, "GraphicsDevice", "Failed to create sampler");
		pSampler->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pSampler);
		return pSampler;
	}

	NODISCARD SharedPtr<Shader> GraphicsDevice::CreateShader(const ShaderDesc& desc)
	{
		SharedPtr<Shader> pShader = CreateShaderHAL(desc);
		DEV_ASSERT(pShader != nullptr, "GraphicsDevice", "Failed to create shader");
		pShader->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pShader);
		return pShader;
	}

	NODISCARD SharedPtr<CommandBuffer> GraphicsDevice::CreateCommandBuffer(const CommandBufferDesc& desc)
	{
		SharedPtr<CommandBuffer> pCommandBuffer = CreateCommandBufferHAL(desc);
		DEV_ASSERT(pCommandBuffer != nullptr, "GraphicsDevice", "Failed to create command buffer");
		pCommandBuffer->_SetOwnerDevice(this);
		mDeviceObjects.push_back(pCommandBuffer);
		return pCommandBuffer;
	}

	NODISCARD SharedPtr<ResourceLayout> GraphicsDevice::CreateResourceLayout(const ResourceLayoutDesc& desc)
	{
		return nullptr;
	}

	NODISCARD SharedPtr<RenderPass> GraphicsDevice::CreateRenderPass(const RenderPassDesc& desc)
	{
		return nullptr;
	}
}
