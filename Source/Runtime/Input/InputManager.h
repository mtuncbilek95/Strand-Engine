#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Manager/ManagerAPI.h>

#include <Runtime/Input/InputSystem.h>

namespace Strand
{
	class RUNTIME_API InputManager : public ManagerAPI<InputManager>
	{
	public:
		InputManager()
		{
			if(mInputSystem == nullptr)
				mInputSystem = SharedPtr<InputSystem>(new InputSystem());
		}
		~InputManager() = default;

		SharedPtr<InputSystem>& GetInputSystem() { return mInputSystem; }
	private:
		SharedPtr<InputSystem> mInputSystem;
	};
}
