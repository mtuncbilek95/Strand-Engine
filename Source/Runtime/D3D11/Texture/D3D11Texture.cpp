#include "D3D11Texture.h"

#include <Runtime/D3D11/Texture/D3D11TextureUtils.h>
#include <Runtime/HAL/Texture/TextureUtils.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

namespace Strand
{
	D3D11Texture::D3D11Texture(const TextureDesc& desc, ID3D11Device* pDevice) : Texture(desc)
	{
		mDevice = pDevice;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = desc.Size.x;
		textureDesc.Height = desc.Size.y;
		textureDesc.MipLevels = desc.MipLevels;
		textureDesc.ArraySize = desc.ArraySize;
		textureDesc.Format = D3D11TextureUtils::GetDXTextureFormat(desc.Format);
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = GetRawData();
		subresourceData.SysMemPitch = GetSize().x * TextureUtils::GetTextureSize(desc.Format);

		DEV_ASSERT(SUCCEEDED(mDevice->CreateTexture2D(&textureDesc, &subresourceData, &mTexture)), "D3D11Texture", "Failed to create D3D11Texture2D");
	}
}
