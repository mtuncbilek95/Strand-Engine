#pragma once

#include <Runtime/Core/Core.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Strand
{
	class RUNTIME_API InputSystem
	{
	public:
		InputSystem();
		~InputSystem() = default;

	private:
		GLFWwindow* mWindowAPI;
	};
}
