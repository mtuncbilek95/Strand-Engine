#include "D3D11TextureView.h"

#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

#include <Runtime/D3D11/Texture/D3D11Texture.h>
#include <Runtime/D3D11/Texture/D3D11TextureUtils.h>
#include <Runtime/HAL/Texture/TextureUtils.h>

namespace Strand
{
	D3D11TextureView::D3D11TextureView(const TextureViewDesc& desc, ID3D11Device* pDevice) : TextureView(desc)
	{
		mDevice = pDevice;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = D3D11TextureUtils::GetDXTextureFormat(desc.pTexture->GetFormat());
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;

		DEV_ASSERT(SUCCEEDED(mDevice->CreateShaderResourceView(((D3D11Texture*)desc.pTexture.get())->GetTexture().Get(), &srvDesc, mShaderResourceView.GetAddressOf())), 
			"D3D11TextureView", "");
	}
}
