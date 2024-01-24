#include "D3D11Sampler.h"

#include <Runtime/D3D11/Device/D3D11Device.h>

#include <Runtime/D3D11/Sampler/D3D11SamplerUtils.h>

namespace Strand
{
	D3D11Sampler::D3D11Sampler(const SamplerDesc& desc, ID3D11Device* pDevice) : Sampler(desc)
	{
		mDevice = pDevice;

		D3D11_SAMPLER_DESC samplerDesc = {};

		samplerDesc.Filter = D3D11SamplerUtils::GetSamplerFilter(desc.Filter);
		samplerDesc.AddressU = D3D11SamplerUtils::GetAddressMode(desc.AddressU);
		samplerDesc.AddressV = D3D11SamplerUtils::GetAddressMode(desc.AddressV);
		samplerDesc.AddressW = D3D11SamplerUtils::GetAddressMode(desc.AddressW);
		samplerDesc.MipLODBias = desc.MipLODBias;
		samplerDesc.MaxAnisotropy = desc.MaxAnisotropy;
		samplerDesc.ComparisonFunc = D3D11SamplerUtils::GetComparisonFunc(desc.SamplerComparison);
		samplerDesc.BorderColor[0] = desc.BorderColor[0];
		samplerDesc.BorderColor[1] = desc.BorderColor[1];
		samplerDesc.BorderColor[2] = desc.BorderColor[2];
		samplerDesc.BorderColor[3] = desc.BorderColor[3];
		samplerDesc.MinLOD = desc.MinLOD;
		samplerDesc.MaxLOD = desc.MaxLOD;
		
		DEV_ASSERT(SUCCEEDED(mDevice->CreateSamplerState(&samplerDesc, mSamplerState.GetAddressOf())), "D3D11Sampler", "Failed to create D3D11Sampler");

		DEV_LOG(SE_VERBOSE, "Created D3D11Sampler");
	}
}
