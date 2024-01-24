#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	class Texture;

	struct RUNTIME_API TextureViewDesc
	{
		uint32 ArraySize;
		uint32 MipLevels;
		Texture* pTexture;
	};
}
