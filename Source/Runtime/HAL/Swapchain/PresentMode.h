#pragma once
#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API PresentMode : byte
	{
		Immediate,
		VsyncImmediate,
		VsyncQueued
	};
}