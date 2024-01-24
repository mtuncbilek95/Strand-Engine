#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Texture/Texture.h>

#include <d3d11.h>

#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11Texture : public Texture
	{
	public:
		D3D11Texture(const TextureDesc& desc, ID3D11Device* pDevice);
		~D3D11Texture() override = default;

		ComPtr<ID3D11Texture2D>& GetTexture() { return mTexture; }
	private:
		ComPtr<ID3D11Texture2D> mTexture;

		ID3D11Device* mDevice;
	};
}
