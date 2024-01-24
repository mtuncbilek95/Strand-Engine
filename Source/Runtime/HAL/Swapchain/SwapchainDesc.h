#pragma once

#include <Runtime/HAL/Texture/TextureFormat.h>
#include <Runtime/HAL/Swapchain/PresentMode.h>
#include <Runtime/HAL/Swapchain/SampleCount.h>

#include <Runtime/Window/Window.h>

namespace Strand
{
	struct RUNTIME_API SwapchainDesc
	{
		byte BufferCount;
		SampleCount MultisampleCount;
		TextureFormat ColorFormat;
		TextureFormat DepthFormat;
		SharedPtr<Window>& pWindow;
		PresentMode PresentMode;
	};
}
