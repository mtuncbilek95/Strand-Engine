#include "InputSystem.h"

#include <Runtime/Window/WindowManager.h>

namespace Strand
{
	InputSystem::InputSystem()
	{
		mWindowAPI = WindowManager::GetInstance().GetMainWindow()->GetWindowHandle();
	}
}
