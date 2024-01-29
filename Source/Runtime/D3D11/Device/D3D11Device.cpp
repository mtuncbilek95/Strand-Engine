#include "D3D11Device.h"

#include <Runtime/D3D11/Swapchain/D3D11Swapchain.h>
#include <Runtime/D3D11/Texture/D3D11Texture.h>
#include <Runtime/D3D11/Texture/D3D11TextureView.h>
#include <Runtime/D3D11/Buffer/D3D11GraphicsBuffer.h>
#include <Runtime/D3D11/Pipeline/D3D11Pipeline.h>
#include <Runtime/D3D11/Sampler/D3D11Sampler.h>
#include <Runtime/D3D11/Shader/D3D11Shader.h>
#include <Runtime/D3D11/ResourceLayout/D3D11ResourceLayout.h>

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

	void D3D11Device::BindPipeline(const SharedPtr<Pipeline>& pipeline)
	{
		for (auto& shader : pipeline->GetShaders())
		{
			switch (shader->GetShaderType())
			{
			case ShaderType::Vertex:
			{
				mD3DImmediateContext->VSSetShader(static_cast<D3D11Shader*>(shader.get())->GetVertexShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Pixel:
			{
				mD3DImmediateContext->PSSetShader(static_cast<D3D11Shader*>(shader.get())->GetPixelShader().Get(), nullptr, 0);
				break;
			}
			default:
			{
				DEV_ASSERT(false, "CommandList", "Invalid shader type.");
				break;
			}
			}
		}

		mD3DImmediateContext->IASetInputLayout(static_cast<D3D11Pipeline*>(pipeline.get())->GetInputLayoutObject().Get());
		float factor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		mD3DImmediateContext->OMSetBlendState(static_cast<D3D11Pipeline*>(pipeline.get())->GetBlendObject().Get(), factor, D3D11_APPEND_ALIGNED_ELEMENT);
		mD3DImmediateContext->OMSetDepthStencilState(static_cast<D3D11Pipeline*>(pipeline.get())->GetDepthStencilObject().Get(), 0);
		mD3DImmediateContext->RSSetState(static_cast<D3D11Pipeline*>(pipeline.get())->GetRasterizerObject().Get());
		mD3DImmediateContext->IASetPrimitiveTopology(static_cast<D3D11Pipeline*>(pipeline.get())->GetPrimitiveObject());
	}

	void D3D11Device::BindVertexBuffer(const ArrayList<SharedPtr<GraphicsBuffer>>& buffers)
	{
		for (uint32 i = 0; i < buffers.size(); i++)
		{
			uint32 stride = buffers[i]->GetStructureByteStride();
			uint32 offset = 0;
			mD3DImmediateContext->IASetVertexBuffers(i, 1, static_cast<D3D11GraphicsBuffer*>(buffers[i].get())->GetBuffer().GetAddressOf(), &stride, &offset);
		}
	}

	void D3D11Device::BindIndexBuffer(const SharedPtr<GraphicsBuffer>& buffer)
	{
		mD3DImmediateContext->IASetIndexBuffer(static_cast<D3D11GraphicsBuffer*>(buffer.get())->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	void D3D11Device::UpdateBuffer(const SharedPtr<GraphicsBuffer>& buffer, const void* data, uint32 size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		mD3DImmediateContext->Map(static_cast<D3D11GraphicsBuffer*>(buffer.get())->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, size);
		mD3DImmediateContext->Unmap(static_cast<D3D11GraphicsBuffer*>(buffer.get())->GetBuffer().Get(), 0);
	}

	void D3D11Device::BindResourceLayout(const SharedPtr<ResourceLayout>& resourceLayout)
	{
		resourceLayout->Bind();
	}

	void D3D11Device::DrawIndexed(const uint32 indexCount, const uint32 indexOffset, const uint32 vertexOffset)
	{
		mD3DImmediateContext->DrawIndexed(indexCount, indexOffset, vertexOffset);
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

	NODISCARD SharedPtr<ResourceLayout> D3D11Device::CreateResourceLayoutHAL(const ResourceLayoutDesc& desc)
	{
		SharedPtr<D3D11ResourceLayout> resourceLayout = std::make_shared<D3D11ResourceLayout>(desc, mD3D11Device.Get());
		return resourceLayout;
	}
}
