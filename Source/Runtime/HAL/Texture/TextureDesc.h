#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Texture/TextureFormat.h>
#include <Runtime/HAL/Texture/TextureUsage.h>
#include <Runtime/HAL/Texture/TextureType.h>

namespace Strand
{
	struct RUNTIME_API TextureDesc
	{
		Vector3u Size;
		uint32 MipLevels;
		uint32 ArraySize;
		TextureFormat Format;
		TextureUsage Usage;
		TextureType Type;
	};
}
