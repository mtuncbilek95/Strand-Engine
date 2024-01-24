#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Pipeline/Blend/BlendOperation.h>
#include <Runtime/HAL/Pipeline/Blend/BlendType.h>
#include <Runtime/HAL/Pipeline/Blend/ColorMask.h>

namespace Strand
{
	struct RUNTIME_API RenderTargetBlendDesc
	{
		bool BlendEnable;
		BlendType SrcBlend;
		BlendType DestBlend;
		BlendOperation BlendOp;
		BlendType SrcBlendAlpha;
		BlendType DestBlendAlpha;
		BlendOperation BlendOpAlpha;
		ColorMask ColorWriteMask;
	};
}
