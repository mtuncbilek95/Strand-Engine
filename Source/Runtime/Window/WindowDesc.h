#pragma once

#include <Runtime/Window/WindowMode.h>

namespace Strand
{
	struct RUNTIME_API WindowDesc
	{
		Vector2u WindowSize;
		Vector2i WindowPosition;
		WindowMode WindowMode;
		String WindowTitle;
	};
}
