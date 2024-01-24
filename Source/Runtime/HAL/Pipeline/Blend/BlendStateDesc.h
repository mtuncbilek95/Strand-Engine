#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Pipeline/Blend/RenderTargetBlendDesc.h>

namespace Strand
{
	struct RUNTIME_API BlendStateDesc
	{
		bool AlphaToCoverageEnable;
		bool IndependentBlendEnable;
		RenderTargetBlendDesc RenderTargetBlendDesc;
	};
}
