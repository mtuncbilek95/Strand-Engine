#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API GraphicsDeviceObjectType : byte
	{
		Swapchain,
		Texture,
		TextureView,
		GraphicsBuffer,
		Shader,
		Sampler,
		Pipeline,
		ResourceLayout
	};
}
