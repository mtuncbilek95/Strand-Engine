#include "D3D11CommandBuffer.h"

#include <Runtime/D3D11/Swapchain/D3D11Swapchain.h>
#include <Runtime/D3D11/Pipeline/D3D11Pipeline.h>
#include <Runtime/D3D11/Shader/D3D11Shader.h>
#include <Runtime/D3D11/Sampler/D3D11Sampler.h>
#include <Runtime/D3D11/Pipeline/D3D11PipelineUtils.h>
#include <Runtime/D3D11/Buffer/D3D11GraphicsBuffer.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>

namespace Strand
{
	D3D11CommandBuffer::D3D11CommandBuffer(ID3D11Device* pDevice)
	{
		mDevice = pDevice;
		mDevice->GetImmediateContext(&mImmediateContext);

		/*DEV_ASSERT(SUCCEEDED(mDevice->CreateDeferredContext(0, mDeferredContext.GetAddressOf())), "D3D11CommandBuffer",
			"Failed to create D3D11CommandBuffer");

		DEV_LOG(SE_VERBOSE, "Created D3D11CommandBuffer");*/
	}

	void D3D11CommandBuffer::InitContext(ID3D11Device* pDevice)
	{
		mDevice = pDevice;
		mDevice->GetImmediateContext(&mImmediateContext);

		DEV_ASSERT(SUCCEEDED(mDevice->CreateDeferredContext(0, mDeferredContext.GetAddressOf())), "D3D11CommandBuffer",
						"Failed to create D3D11CommandBuffer");

		DEV_LOG(SE_VERBOSE, "Created D3D11CommandBuffer");
	}

	void D3D11CommandBuffer::BindPipeline(const SharedPtr<Pipeline>& pipeline)
	{
		for (auto& shader : pipeline->GetShaders())
		{
			switch (shader->GetShaderType())
			{
			case ShaderType::Vertex:
			{
				mImmediateContext->VSSetShader(static_cast<D3D11Shader*>(shader.get())->GetVertexShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Pixel:
			{
				mImmediateContext->PSSetShader(static_cast<D3D11Shader*>(shader.get())->GetPixelShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Geometry:
			{
				mImmediateContext->GSSetShader(static_cast<D3D11Shader*>(shader.get())->GetGeometryShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Domain:
			{
				mImmediateContext->DSSetShader(static_cast<D3D11Shader*>(shader.get())->GetDomainShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Hull:
			{
				mImmediateContext->HSSetShader(static_cast<D3D11Shader*>(shader.get())->GetHullShader().Get(), nullptr, 0);
				break;
			}
			case ShaderType::Compute:
			{
				mImmediateContext->CSSetShader(static_cast<D3D11Shader*>(shader.get())->GetComputeShader().Get(), nullptr, 0);
				break;
			}
			default:
				break;
			}
		}

		if (pipeline->GetSampler())
		{
			mImmediateContext->PSSetSamplers(0, 1, static_cast<D3D11Sampler*>(pipeline->GetSampler().get())->GetSamplerState().GetAddressOf());
		}

		mImmediateContext->OMSetRenderTargets(1,
			static_cast<D3D11Swapchain*>(GraphicsManager::GetInstance().GetDevice()->GetMainSwapchain().get())->GetRenderTarget().GetAddressOf(), 
			static_cast<D3D11Swapchain*>(GraphicsManager::GetInstance().GetDevice()->GetMainSwapchain().get())->GetDepthStencil().Get());
		mImmediateContext->IASetInputLayout(static_cast<D3D11Pipeline*>(pipeline.get())->GetInputLayout().Get());
		mImmediateContext->IASetPrimitiveTopology(D3D11PipelineUtils::GetPrimitiveTopology(pipeline->GetPrimitiveMode()));
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		mImmediateContext->OMSetBlendState(static_cast<D3D11Pipeline*>(pipeline.get())->GetBlendState().Get(), blendFactor, D3D11_APPEND_ALIGNED_ELEMENT);
		mImmediateContext->OMSetDepthStencilState(static_cast<D3D11Pipeline*>(pipeline.get())->GetDepthStencilState().Get(), 0);
		mImmediateContext->RSSetState(static_cast<D3D11Pipeline*>(pipeline.get())->GetRasterizerState().Get());
	}

	void D3D11CommandBuffer::BindViewport()
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width = float(WindowManager::GetInstance().GetMainWindow()->GetWindowSize().x);
		viewport.Height = float(WindowManager::GetInstance().GetMainWindow()->GetWindowSize().y);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		mImmediateContext->RSSetViewports(1, &viewport);
	}

	void D3D11CommandBuffer::BindVertexBuffer(const SharedPtr<GraphicsBuffer>& vertexBuffer)
	{
		uint32 stride = vertexBuffer->GetStructureByteStride();
		uint32 offset = 0;

		mImmediateContext->IASetVertexBuffers(0, 1, static_cast<D3D11GraphicsBuffer*>(vertexBuffer.get())->GetBuffer().GetAddressOf(), &stride, &offset);
	}

	void D3D11CommandBuffer::BindIndexBuffer(const SharedPtr<GraphicsBuffer>& indexBuffer)
	{
		mImmediateContext->IASetIndexBuffer(static_cast<D3D11GraphicsBuffer*>(indexBuffer.get())->GetBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	void D3D11CommandBuffer::BindResourceLayout(const SharedPtr<ResourceLayout>& resourceLayout)
	{
		ID3D11ShaderResourceView* srvs[16] = {};
		ID3D11SamplerState* samplersStates[16] = {};
		ID3D11Buffer* buffers[16] = {};
		
		ShaderStage stage = ShaderStage::Vertex;

		switch (stage)
		{
		case ShaderStage::Vertex:
		{
			mDeferredContext->VSSetShaderResources(0, (uint32)(0), srvs);
			mDeferredContext->VSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->VSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		case ShaderStage::Pixel:
		{
			mDeferredContext->PSSetShaderResources(0, (uint32)0, srvs);
			mDeferredContext->PSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->PSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		case ShaderStage::Compute:
		{
			mDeferredContext->CSSetShaderResources(0, (uint32)0, srvs);
			mDeferredContext->CSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->CSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		case ShaderStage::Geometry:
		{
			mDeferredContext->GSSetShaderResources(0, (uint32)0, srvs);
			mDeferredContext->GSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->GSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		case ShaderStage::Hull:
		{
			mDeferredContext->HSSetShaderResources(0, (uint32)0, srvs);
			mDeferredContext->HSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->HSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		case ShaderStage::Domain:
		{
			mDeferredContext->DSSetShaderResources(0, (uint32)0, srvs);
			mDeferredContext->DSSetSamplers(0, (uint32)0, samplersStates);
			mDeferredContext->DSSetConstantBuffers(0, (uint32)0, buffers);
			break;
		}
		default:
		{
			DEV_ASSERT(false, "CommandList", "Invalid shader stage.");
			break;
		}
		}
	}

	void D3D11CommandBuffer::DrawIndex(const uint32 indexCount, const uint32 indexOffset, const uint32 vertexOffset)
	{
		mImmediateContext->DrawIndexed(indexCount, indexOffset, vertexOffset);
	}

	void D3D11CommandBuffer::Draw(const uint32 vertexCount, const uint32 vertexOffset)
	{
		mImmediateContext->Draw(vertexCount, vertexOffset);
	}

	void D3D11CommandBuffer::DrawInstanced(const uint32 vertexCount, const uint32 vertexOffset, const uint32 instanceCount, const uint32 instanceOffset)
	{
		mImmediateContext->DrawInstanced(vertexCount, instanceCount, vertexOffset, instanceOffset);
	}

	void D3D11CommandBuffer::ClearColor(const Vector4f& color)
	{
		float clearColor[4] = { color.x, color.y, color.z, color.w };
		mImmediateContext->ClearRenderTargetView(static_cast<D3D11Swapchain*>(GraphicsManager::GetInstance().GetDevice()->GetMainSwapchain().get())->GetRenderTarget().Get(), clearColor);
		mImmediateContext->ClearDepthStencilView(static_cast<D3D11Swapchain*>(GraphicsManager::GetInstance().GetDevice()->GetMainSwapchain().get())->GetDepthStencil().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3D11CommandBuffer::Reset()
	{
		mCommandList.Reset();
		mDeferredContext->FinishCommandList(false, mCommandList.GetAddressOf());
	}
}
