#pragma once

#include <Runtime/HAL/Device/GraphicsAPI.h>
#include <Runtime/HAL/Texture/TextureFormat.h>

namespace Strand
{
	class Window;
	struct RUNTIME_API GraphicsDeviceDesc
	{
		GraphicsAPI UsedAPI;
		SharedPtr<Window>& pWindow;
		TextureFormat ColorFormat;
		TextureFormat DepthFormat;
		byte BufferCount;
	};
}
