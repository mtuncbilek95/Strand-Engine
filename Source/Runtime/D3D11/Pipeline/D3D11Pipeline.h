#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Pipeline/Pipeline.h>
#include <Runtime/D3D11/Pipeline/D3D11PipelineUtils.h>

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

		ComPtr<ID3D11InputLayout>& GetInputLayoutObject() { return mInputLayout; }
		ComPtr<ID3D11RasterizerState>& GetRasterizerObject() { return mRasterizerState; }
		ComPtr<ID3D11DepthStencilState>& GetDepthStencilObject() { return mDepthStencilState; }
		ComPtr<ID3D11BlendState>& GetBlendObject() { return mBlendState; }
		ComPtr<ID3D11SamplerState>& GetSamplerObject() { return mSamplerState; }
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveObject() { return D3D11PipelineUtils::GetPrimitiveTopology(GetPrimitiveMode()); }

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
