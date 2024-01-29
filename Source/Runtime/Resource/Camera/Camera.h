#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Window/WindowManager.h>

namespace Strand
{
	class RUNTIME_API Camera
	{
	public:
		Camera() = default;
		~Camera() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void UpdateInput(float deltaTime) = 0;
	};
}
