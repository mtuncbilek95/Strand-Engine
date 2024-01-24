#include "Window.h"

#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

namespace Strand
{

	Window::Window(const WindowDesc& desc) : mWindowHandle(nullptr), mWindowMode(desc.WindowMode),
		mWindowSize(desc.WindowSize), mWindowName(desc.WindowTitle), mWindowPosition(desc.WindowPosition)
	{
		DEV_ASSERT(glfwInit(), "Window", "Failed to initialize glfw");
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		mWindowHandle = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mWindowName.c_str(), nullptr, nullptr);
		glfwSetWindowPos(mWindowHandle, mWindowPosition.x, mWindowPosition.y);

		glfwShowWindow(mWindowHandle);

		DEV_ASSERT(mWindowHandle != nullptr, "Window", "Failed to create window");

		DEV_LOG(SE_VERBOSE, "Created window with size: { %d, %d }", mWindowSize.x, mWindowSize.y);

		glfwSetWindowUserPointer(mWindowHandle, this);

		glfwSetWindowSizeCallback(mWindowHandle, [](GLFWwindow* window, int width, int height)
			{
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->mWindowSize = uvec2(width, height);
				GraphicsManager::GetInstance().GetDevice()->GetMainSwapchain()->Resize(win->mWindowSize);
			});
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::PollMessages()
	{
		glfwSwapBuffers(mWindowHandle);
		glfwPollEvents();
	}
}