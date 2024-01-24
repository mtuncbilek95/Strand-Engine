#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Window/Window.h>
#include <Runtime/Manager/ManagerAPI.h>


namespace Strand
{
	class RUNTIME_API WindowManager : public ManagerAPI<WindowManager>
	{
	public:
		WindowManager() = default;
		~WindowManager() = default;

		SharedPtr<Window> CreateMainWindow(const WindowDesc& desc)
		{
			if(mWindow == nullptr)
				mWindow = SharedPtr<Window>(new Window(desc));
			return mWindow;
		}

		SharedPtr<Window>& GetMainWindow() { return mWindow; }

	private:
		SharedPtr<Window> mWindow;
	};
}
