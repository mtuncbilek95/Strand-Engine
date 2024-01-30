#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resource/Camera/Camera.h>
#include <Runtime/Resource/Camera/FreeLookCamera.h>
#include <Runtime/Resource/Camera/CameraType.h>
#include <Runtime/Manager/ManagerAPI.h>

namespace Strand
{
	class RUNTIME_API CameraManager : public ManagerAPI<CameraManager>
	{
	public:
		CameraManager() = default;
		~CameraManager() = default;

		SharedPtr<Camera> CreateCamera(CameraType type)
		{
			if (mCamera == nullptr)
			{
				switch (type)
				{
				case CameraType::FreeLook:
					mCamera = std::make_shared<FreeLookCamera>();
					break;
				default:
					break;
				}
			}
			return mCamera;
		}

		SharedPtr<Camera>& GetCamera() { return mCamera; }

	private:
		SharedPtr<Camera> mCamera;
	};
}
