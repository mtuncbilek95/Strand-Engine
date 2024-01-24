#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Texture/TextureView.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11TextureView : public TextureView
	{
	public:
		D3D11TextureView(const TextureViewDesc& desc, ID3D11Device* pDevice);
		~D3D11TextureView() override = default;

		ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() { return mShaderResourceView; }

	private:
		ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
		ID3D11Device* mDevice;
	};
}
