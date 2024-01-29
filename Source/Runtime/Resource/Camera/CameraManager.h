#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resource/Camera/Camera.h>
#include <Runtime/Resource/Camera/FreeLookCamera.h>
#include <Runtime/Manager/ManagerAPI.h>

namespace Strand
{
	class RUNTIME_API CameraManager : public ManagerAPI<CameraManager>
	{
	public:
		CameraManager() = default;
		~CameraManager() = default;

		SharedPtr<FreeLookCamera> CreateCamera()
		{
			if (mCamera == nullptr)
				mCamera = std::make_shared<FreeLookCamera>();
			return mCamera;
		}

		SharedPtr<FreeLookCamera>& GetFreeLookCamera() { return mCamera; }

	private:
		SharedPtr<FreeLookCamera> mCamera;
	};
}
