#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Texture/TextureResult.h>

namespace Strand
{
	class RUNTIME_API TextureLoader
	{
	public:
		TextureLoader() = delete;
		~TextureLoader() = delete;

		static TextureResult LoadTexture(const String& path);
	};
}
