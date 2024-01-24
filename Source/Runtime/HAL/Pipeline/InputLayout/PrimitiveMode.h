#pragma once

#include <Runtime/Core/Core.h>

namespace Strand
{
	enum class RUNTIME_API PrimitiveMode : byte
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};
}
