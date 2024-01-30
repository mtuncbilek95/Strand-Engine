#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Camera/CameraManager.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/HAL/ResourceLayout/ResourceLayout.h>

namespace Strand
{
	struct RUNTIME_API TransformData
	{
		Matrix4f World;
		Matrix4f View;
		Matrix4f Projection;
	};

	struct RUNTIME_API Transform
	{
		Transform()
		{
			mPosition = Vector3f(0.0f, 0.0f, 0.0f);
			mRotation = { 0.0f, 0.0f, 0.0f };
			mScale = Vector3f(1.0f, 1.0f, 1.0f);

			mTransformData.World = XMMatrixIdentity();
			mTransformData.View = XMMatrixIdentity();
			mTransformData.Projection = XMMatrixIdentity();

			GraphicsBufferDesc transformBufferDesc;
			transformBufferDesc.Usage = BufferUsage::ConstantBuffer;
			transformBufferDesc.CPUAccess = BufferCPUAccess::Write;
			transformBufferDesc.MiscFlags = 0;
			transformBufferDesc.SizeInBytes = sizeof(TransformData) * 3;
			transformBufferDesc.StructureByteStride = sizeof(TransformData);
			transformBufferDesc.ResourceUsage = ResourceUsage::Dynamic;
			transformBufferDesc.InitialData = &mTransformData;

			mConstantBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(transformBufferDesc);

			ResourceLayoutDesc vertexLayoutDesc;
			vertexLayoutDesc.Stage = ShaderStage::Vertex;
			vertexLayoutDesc.GraphicsViews = { mConstantBuffer };

			mConstantBufferLayout = GraphicsManager::GetInstance().GetDevice()->CreateResourceLayout(vertexLayoutDesc);
		}

		~Transform() = default;

		Vector3f mPosition;
		Vector3f mRotation;
		Vector3f mScale;

	private:
		friend class GameObject;

		void UpdateWorldMatrix()
		{
			mTransformData.World = XMMatrixTranspose(XMMatrixScaling(mScale.x, mScale.y, mScale.z) *
				XMMatrixRotationRollPitchYaw(XMConvertToRadians(mRotation.x), XMConvertToRadians(mRotation.y), XMConvertToRadians(mRotation.z)) *
				XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z));

			mTransformData.View = CameraManager::GetInstance().GetCamera()->GetViewMatrix();
			mTransformData.Projection = CameraManager::GetInstance().GetCamera()->GetProjectionMatrix();
		}

		TransformData mTransformData;
		SharedPtr<GraphicsBuffer> mConstantBuffer;
		SharedPtr<ResourceLayout> mConstantBufferLayout;
	};
}
