#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Sampler/Sampler.h>

#include <d3d11_4.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11Sampler : public Sampler
	{
	public:
		D3D11Sampler(const SamplerDesc& desc, ID3D11Device* pDevice);
		~D3D11Sampler() override = default;

		ComPtr<ID3D11SamplerState>& GetSamplerState() { return mSamplerState; }
		ID3D11Device* GetDevice() { return mDevice; }

	private:
		ComPtr<ID3D11SamplerState> mSamplerState;
		ID3D11Device* mDevice;
	};
}
