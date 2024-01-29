#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Texture/Texture.h>
#include <Runtime/HAL/Texture/TextureView.h>
#include <Runtime/HAL/Texture/TextureResult.h>

namespace Strand
{
	class RUNTIME_API TextureResource
	{
	public:
		TextureResource(const TextureResult& desc);
		~TextureResource() = default;

		const SharedPtr<Texture>& GetTexture() const { return mTexture; }
		const SharedPtr<TextureView>& GetTextureView() const { return mTextureView; }

	private:
		SharedPtr<Texture> mTexture;
		SharedPtr<TextureView> mTextureView;
	};
}
