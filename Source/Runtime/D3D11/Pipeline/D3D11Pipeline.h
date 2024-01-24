#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Pipeline/Pipeline.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11Pipeline : public Pipeline
	{
	public:
		D3D11Pipeline(const GraphicsPipelineDesc& desc, ID3D11Device* pDevice);
		~D3D11Pipeline() override = default;

		ComPtr<ID3D11InputLayout>& GetInputLayout() { return mInputLayout; }
		ComPtr<ID3D11RasterizerState>& GetRasterizerState() { return mRasterizerState; }
		ComPtr<ID3D11DepthStencilState>& GetDepthStencilState() { return mDepthStencilState; }
		ComPtr<ID3D11BlendState>& GetBlendState() { return mBlendState; }
		ComPtr<ID3D11SamplerState>& GetSamplerState() { return mSamplerState; }

		void OnShutdown() override {};

	private:
		ComPtr<ID3D11InputLayout> mInputLayout;
		ComPtr<ID3D11RasterizerState> mRasterizerState;
		ComPtr<ID3D11DepthStencilState> mDepthStencilState;
		ComPtr<ID3D11BlendState> mBlendState;
		ComPtr<ID3D11SamplerState> mSamplerState;

		ID3D11Device* mDevice;
	};
}
