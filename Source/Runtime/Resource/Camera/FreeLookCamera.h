#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Camera/Camera.h>

namespace Strand
{
	class RUNTIME_API FreeLookCamera : public Camera
	{
	public:
		FreeLookCamera();
		~FreeLookCamera() = default;

		virtual void Update(float deltaTime) override;
		virtual void UpdateInput(float deltaTime) override;
	};
}
