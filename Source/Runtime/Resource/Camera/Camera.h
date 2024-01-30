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

		Matrix4f GetViewMatrix() const { return mViewMatrix; }
		Matrix4f GetProjectionMatrix() const { return mProjectionMatrix; }
		Vector3f GetPosition() const { return mPosition; }

	protected:
		Vector3f mPosition = { 0.0f, 0.0f, 0.0f };
		Vector3f mOrientation = { 0.0f, 0.0f, -1.0f };
		Vector3f mUp = { 0.0f, 1.0f, 0.0f };

		bool mIsDirty = true;
		Vector2u mViewportSize = WindowManager::GetInstance().GetMainWindow()->GetWindowSize();
		float mAspectRatio = 0.0f;
		float mFieldOfView = 0.0f;
		float mNearPlane = 0.0f;
		float mFarPlane = 0.0f;

		float mSpeed = 0.1f;
		float mSensitivity = 100.f;

		Matrix4f mProjectionMatrix = XMMatrixIdentity();
		Matrix4f mViewMatrix = XMMatrixIdentity();

		GLFWwindow* mWindowHandle = WindowManager::GetInstance().GetMainWindow()->GetWindowHandle();

		XMFLOAT3 RotateVector(XMFLOAT3 vector, float angle, XMFLOAT3 axis)
		{
			XMVECTOR xmVector = XMLoadFloat3(&vector);
			XMVECTOR xmAxis = XMLoadFloat3(&axis);
			XMMATRIX rotationMatrix = XMMatrixRotationAxis(xmAxis, XMConvertToRadians(angle));
			xmVector = XMVector3TransformCoord(xmVector, rotationMatrix);
			XMStoreFloat3(&vector, xmVector);
			return vector;
		}
	};
}
