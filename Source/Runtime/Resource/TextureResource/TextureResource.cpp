#include "TextureResource.h"

#include <Runtime/HAL/Manager/GraphicsManager.h>

namespace Strand
{
	TextureResource::TextureResource(const TextureResult& desc)
	{
		TextureDesc textureDesc;
		textureDesc.Size = XMUINT3(desc.Size.x, desc.Size.y, 1);
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = TextureFormat::RGBA8_UNorm;
		textureDesc.Type = TextureType::Texture2D;
		textureDesc.Usage = TextureUsage::Shader_Input;
		textureDesc.RawData = desc.Data;

		mTexture = GraphicsManager::GetInstance().GetDevice()->CreateTexture(textureDesc);

		TextureViewDesc textureViewDesc;
		textureViewDesc.pTexture = mTexture;
		textureViewDesc.ArraySize = 1;
		textureViewDesc.MipLevels = 1;

		mTextureView = GraphicsManager::GetInstance().GetDevice()->CreateTextureView(textureViewDesc);
	}
}
