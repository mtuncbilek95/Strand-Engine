#include "DamagedHelmet.h"

namespace Strand
{
	DamagedHelmet::DamagedHelmet() : GameObject()
	{
		MeshLoader::LoadSingleMesh(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\DamagedHelmet.gltf)", mMesh);
		TextureResult baseColorTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_albedo.jpg)");
		TextureResult normalTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_normal.jpg)");
		TextureResult emmisiveTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_emissive.jpg)");
		TextureResult ambientTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_AO.jpg)");
		TextureResult metalRoughTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_metalRoughness.jpg)");

		mMaterial->SetBaseColor(baseColorTex);
		mMaterial->SetNormal(normalTex);
		mMaterial->SetEmissive(emmisiveTex);
		mMaterial->SetAmbientOcclusion(ambientTex);
		mMaterial->SetMetallic(metalRoughTex);
	}
	void DamagedHelmet::Start()
	{
		GameObject::Start();
		mTransform.mRotation = { 90.0f, 180.0f, 0.0f };
	}
	void DamagedHelmet::Update()
	{
		GameObject::Update();
		mTransform.mRotation.y += 0.1f;
	}
	void DamagedHelmet::Stop()
	{
		GameObject::Stop();
	}
}
