#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API ShaderStage : byte
	{
		Vertex,
		Pixel,
		Geometry,
		Hull,
		Domain,
		Compute
	};
}
