#include "D3D11ResourceLayout.h"

#include <Runtime/D3D11/Texture/D3D11TextureView.h>
#include <Runtime/D3D11/Buffer/D3D11GraphicsBuffer.h>
#include <Runtime/D3D11/Sampler/D3D11Sampler.h>

namespace Strand
{
	D3D11ResourceLayout::D3D11ResourceLayout(const ResourceLayoutDesc& desc, ID3D11Device* pDevice) : ResourceLayout(desc)
	{
		mD3D11Device = pDevice;
		mD3D11Device->GetImmediateContext(&mD3D11Context);
	}

	void D3D11ResourceLayout::Bind() const noexcept
	{
		ID3D11ShaderResourceView* srvs[16];
		ID3D11SamplerState* samplers[16];
		ID3D11Buffer* cbuffers[16];

		for (int i = 0; i < GetTextureViews().size(); i++)
		{
			srvs[i] = static_cast<D3D11TextureView*>(GetTextureViews()[i].get())->GetShaderResourceView().Get();
		}

		for (int i = 0; i < GetSamplers().size(); i++)
		{
			samplers[i] = static_cast<D3D11Sampler*>(GetSamplers()[i].get())->GetSamplerState().Get();
		}

		for (int i = 0; i < GetGraphicsBuffers().size(); i++)
		{
			cbuffers[i] = static_cast<D3D11GraphicsBuffer*>(GetGraphicsBuffers()[i].get())->GetBuffer().Get();
		}

		switch (GetStage())
		{
		case ShaderStage::Vertex:
		{
			mD3D11Context->VSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->VSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->VSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		case ShaderStage::Pixel:
		{
			mD3D11Context->PSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->PSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->PSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		case ShaderStage::Compute:
		{
			mD3D11Context->CSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->CSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->CSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		case ShaderStage::Geometry:
		{
			mD3D11Context->GSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->GSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->GSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		case ShaderStage::Hull:
		{
			mD3D11Context->HSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->HSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->HSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		case ShaderStage::Domain:
		{
			mD3D11Context->DSSetShaderResources(0, GetTextureViews().size(), srvs);
			mD3D11Context->DSSetSamplers(0, GetSamplers().size(), samplers);
			mD3D11Context->DSSetConstantBuffers(0, GetGraphicsBuffers().size(), cbuffers);
			break;
		}
		default:
			break;
		}
	}
}
