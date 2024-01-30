#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/Resource/Mesh/Mesh.h>
#include <Runtime/Resource/MeshLoader/MeshLoader.h>
#include <Runtime/Resource/TextureLoader/TextureLoader.h>
#include <Runtime/Resource/Material/Material.h>
#include <Runtime/World/Transform.h>

#include <Runtime/Resource/Game/LightObject.h>

namespace Strand
{
	class RUNTIME_API GameObject
	{
	public:
		GameObject() 
		{
			mMesh = std::make_shared<Mesh>();
			mMaterial = std::make_shared<Material>();
		}
		~GameObject() = default;

		virtual void Start()
		{
			mAmbientLight = {};

			XMFLOAT3 pos = CameraManager::GetInstance().GetCamera()->GetPosition();
			mAmbientLight.cameraPosition = XMLoadFloat3(&pos);
			mAmbientLight.ambientColor = { 0.1f, 0.1f, 0.1f };
			float ambientIntensity = 0.6f;
			mAmbientLight.ambientIntensity = XMLoadFloat(&ambientIntensity);
			mAmbientLight.lightColor = { 0.2f, 0.3f, 0.6f };
			ambientIntensity = 3.0f;
			mAmbientLight.lightIntensity = XMLoadFloat(&ambientIntensity);
			mAmbientLight.lightPosition = { 5.0f, 5.0f, 5.0f };

			GraphicsBufferDesc ambientDesc = {};
			ambientDesc.Usage = BufferUsage::ConstantBuffer;
			ambientDesc.CPUAccess = BufferCPUAccess::Write;
			ambientDesc.MiscFlags = 0;
			ambientDesc.SizeInBytes = sizeof(AmbientLightObject);
			ambientDesc.StructureByteStride = sizeof(XMVECTOR);
			ambientDesc.ResourceUsage = ResourceUsage::Dynamic;
			ambientDesc.InitialData = &mAmbientLight;

			mLightBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(ambientDesc);

			ResourceLayoutDesc pixelLayoutDesc;
			pixelLayoutDesc.Stage = ShaderStage::Pixel;
			pixelLayoutDesc.Samplers = { mMaterial->GetSampler()};
			pixelLayoutDesc.TextureViews = { mMaterial->GetBaseColor()->GetTextureView(), mMaterial->GetEmissive()->GetTextureView(),
				mMaterial->GetNormal()->GetTextureView(), mMaterial->GetAmbientOcclusion()->GetTextureView(), mMaterial->GetMetallic()->GetTextureView() };
			pixelLayoutDesc.GraphicsViews = { mLightBuffer };

			mMaterial->GetPixelLayout() = GraphicsManager::GetInstance().GetDevice()->CreateResourceLayout(pixelLayoutDesc);
		}

		virtual void Update()
		{
			XMFLOAT3 pos = CameraManager::GetInstance().GetCamera()->GetPosition();
			mAmbientLight.cameraPosition = XMLoadFloat3(&pos);
			GraphicsManager::GetInstance().GetDevice()->UpdateBuffer(mLightBuffer, &mAmbientLight, sizeof(mAmbientLight));
			mTransform.UpdateWorldMatrix();
			GraphicsManager::GetInstance().GetDevice()->BindResourceLayout(mTransform.mConstantBufferLayout);
			
			GraphicsManager::GetInstance().GetDevice()->BindResourceLayout(mMaterial->GetPixelLayout());
			GraphicsManager::GetInstance().GetDevice()->BindVertexBuffer({ mMesh->GetPositionBuffer(), mMesh->GetTexCoordBuffer(), mMesh->GetNormalBuffer() });
			GraphicsManager::GetInstance().GetDevice()->BindIndexBuffer(mMesh->GetIndexBuffer());
			GraphicsManager::GetInstance().GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
			GraphicsManager::GetInstance().GetDevice()->UpdateBuffer(mTransform.mConstantBuffer, &mTransform.mTransformData, sizeof(TransformData));

		}

		virtual void Stop() {}

	protected:
		SharedPtr<Mesh> mMesh;
		SharedPtr<Material> mMaterial;
		Transform mTransform;

		SharedPtr<GraphicsBuffer> mLightBuffer;
		AmbientLightObject mAmbientLight;
	};
}
