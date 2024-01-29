#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

#include <Runtime/HAL/Sampler/Sampler.h>
#include <Runtime/HAL/Shader/Shader.h>
#include <Runtime/Resource/ShaderLoader/ShaderLoader.h>

#include <Runtime/HAL/Pipeline/Pipeline.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>

#include <Runtime/Resource/MeshLoader/MeshLoader.h>
#include <Runtime/Resource/Mesh/Mesh.h>
#include <Runtime/Resource/TextureLoader/TextureLoader.h>
#include <Runtime/Resource/TextureResource/TextureResource.h>

#include <Runtime/HAL/ResourceLayout/ResourceLayout.h>

#include <Runtime/Resource/Camera/CameraManager.h>
#include <Runtime/Resource/Camera/FreeLookCamera.h>

using namespace Strand;
void TestGraphics();

int main()
{
	TestGraphics();
	return 0;
}

#pragma region "TestGraphics"

struct Vertex
{
	Vector3f Position;
	Vector3f Color;
};

ArrayList<Vertex> triangle =
{
	{ {-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f} },
	{ { 0.0f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.0f} },
	{ { 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f} }
};

ArrayList<Vertex> triangle2 =
{
	{ {-0.2f, -0.2f, -0.5f}, {1.0f, 0.0f, 0.0f} },
	{ { 0.3f,  0.8f, -0.5f}, {0.0f, 1.0f, 0.0f} },
	{ { 0.8f, -0.2f, -0.5f}, {0.0f, 0.0f, 1.0f} }
};

ArrayList<uint16> indices = { 0, 1, 2 };
ArrayList<uint16> indices2 = { 0, 1, 2 };

struct ConstantBuffer
{
	Matrix4f Model = XMMatrixIdentity();
	Matrix4f View = XMMatrixIdentity();
	Matrix4f Projection = XMMatrixIdentity();
};

void TestGraphics()
{
	WindowDesc windowDesc
	{
		.WindowSize = { 2560, 1440 },
		.WindowPosition = { (2560 - 2560) / 2, (1440 - 1440) / 2 },
		.WindowMode = WindowMode::Windowed,
		.WindowTitle = "Strand Test"
	};

	SharedPtr<Window> window = WindowManager::GetInstance().CreateMainWindow(windowDesc);

	GraphicsDeviceDesc desc
	{
		.UsedAPI = GraphicsAPI::D3D11,
		.pWindow = window
	};

	SharedPtr<GraphicsDevice> device = GraphicsManager::GetInstance().CreateDevice(desc);

	SwapchainDesc swapchainDesc
	{
		.BufferCount = 3,
		.MultisampleCount = SampleCount::Sample_8,
		.ColorFormat = TextureFormat::RGBA8_UNorm,
		.DepthFormat = TextureFormat::D24_UNorm_S8_UInt,
		.pWindow = window,
		.PresentMode = PresentMode::VsyncQueued
	};

	SharedPtr<Swapchain> swapchain = device->CreateSwapchain(swapchainDesc);

	ShaderDesc vertexShaderDesc
	{
		.ShaderName = "ObjectVertexShader",
		.EntryName = "vs_main",
		.ShaderModel = "vs_5_0",
		.Type = ShaderType::Vertex,
		.Source = ShaderLoader::LoadShader("ObjectVertexShader")
	};

	SharedPtr<Shader> vertexShader = device->CreateShader(vertexShaderDesc);

	ShaderDesc pixelShaderDesc
	{
		.ShaderName = "ObjectPixelShader",
		.EntryName = "ps_main",
		.ShaderModel = "ps_5_0",
		.Type = ShaderType::Pixel,
		.Source = ShaderLoader::LoadShader("ObjectPixelShader")
	};

	SharedPtr<Shader> pixelShader = device->CreateShader(pixelShaderDesc);

	SamplerDesc samplerDesc
	{
		.Filter = SamplerFilter::MinMagMipLinear,
		.AddressU = AddressMode::Wrap,
		.AddressV = AddressMode::Wrap,
		.AddressW = AddressMode::Wrap,
		.MipLODBias = 0.0f,
		.MaxAnisotropy = 1,
		.SamplerComparison = SamplerComparison::Never,
		.BorderColor = { 0.0f, 0.0f, 0.0f, 0.0f },
		.MinLOD = 0.0f,
		.MaxLOD = 0.0f
	};

	SharedPtr<Sampler> sampler = device->CreateSampler(samplerDesc);

	GraphicsPipelineDesc pipelineDesc
	{
		.Shaders = { vertexShader, pixelShader },
		.InputLayout =
		{
			{ SemanticName::Position, TextureFormat::RGB32_Float, 0 , 0 , 0xffffffff, SlotClass::PerVertexData, 0 },
			{ SemanticName::TexCoord, TextureFormat::RG32_Float, 0 , 1 , 0xffffffff, SlotClass::PerVertexData, 0 },
			{ SemanticName::Normal, TextureFormat::RGB32_Float, 0 , 2 , 0xffffffff, SlotClass::PerVertexData, 0 }
		},
		.Rasterizer = { FillMode::Solid, CullMode::Back, FaceOrdering::Clockwise, 0, 0, 0, false, false, true, true },
		.DepthStencil = { true, DepthMask::All, DepthStencilComparisonFunc::Less, false, 0xFF, 0xFF },
		.Blend = { false, true, { true, BlendType::One, BlendType::Zero, BlendOperation::Add, BlendType::One, BlendType::Zero, BlendOperation::Add, ColorMask::All } },
		.Sampler = sampler,
		.PrimitiveMode = PrimitiveMode::TriangleList
	};

	SharedPtr<Pipeline> pipeline = device->CreateGraphicsPipeline(pipelineDesc);

	auto mesh = std::make_shared<Mesh>();

	MeshLoader::LoadSingleMesh(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\DamagedHelmet.gltf)", mesh);
	TextureResult baseColorTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_albedo.jpg)");
	TextureResult normalTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_normal.jpg)");
	TextureResult emmisiveTex = TextureLoader::LoadTexture(R"(D:\Projects\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_emissive.jpg)");

	auto baseColor = std::make_shared<TextureResource>(baseColorTex);
	auto normal = std::make_shared<TextureResource>(normalTex);
	auto emmisive = std::make_shared<TextureResource>(emmisiveTex);

	ResourceLayoutDesc pixelLayoutDesc;
	pixelLayoutDesc.Stage = ShaderStage::Pixel;
	pixelLayoutDesc.Samplers = { sampler };
	pixelLayoutDesc.TextureViews = { baseColor->GetTextureView(), normal->GetTextureView(), emmisive->GetTextureView() };

	SharedPtr<ResourceLayout> pixelLayout = device->CreateResourceLayout(pixelLayoutDesc);

	ConstantBuffer constantBuffer;
	constantBuffer.Model = XMMatrixTranspose(XMMatrixRotationY(XMConvertToRadians(180.0f)) * XMMatrixRotationX(XMConvertToRadians(270.0f)) * XMMatrixTranslation(0.0f, 0.0f, 0.0f) * XMMatrixScaling(1.0f, 1.0f, 1.0f));
	constantBuffer.View = XMMatrixTranspose(XMMatrixLookAtLH({ 0.0f, 0.0f, -2.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
	constantBuffer.Projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f));

	GraphicsBufferDesc constantBufferDesc;
	constantBufferDesc.Usage = BufferUsage::ConstantBuffer;
	constantBufferDesc.StructureByteStride = sizeof(ConstantBuffer);
	constantBufferDesc.SizeInBytes = sizeof(ConstantBuffer) * 3;
	constantBufferDesc.ResourceUsage = ResourceUsage::Dynamic;
	constantBufferDesc.CPUAccess = BufferCPUAccess::Write;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.InitialData = &constantBuffer;

	SharedPtr<GraphicsBuffer> cBuffer = device->CreateGraphicsBuffer(constantBufferDesc);

	ResourceLayoutDesc vertexLayoutDesc;
	vertexLayoutDesc.Stage = ShaderStage::Vertex;
	vertexLayoutDesc.GraphicsViews = { cBuffer };

	SharedPtr<ResourceLayout> vertexLayout = device->CreateResourceLayout(vertexLayoutDesc);

	auto camera = CameraManager::GetInstance().CreateCamera();

	while (window->ShouldClose())
	{
		window->PollMessages();

		constantBuffer.Projection = camera->GetProjectionMatrix();
		constantBuffer.View = camera->GetViewMatrix();

		camera->Update(0);
		camera->UpdateInput(0);

		device->ClearColor({ 0.2f, 0.3f, 0.4f, 1.0f });
		device->BindRenderPass();
		device->BindPipeline(pipeline);

		device->BindResourceLayout(pixelLayout);
		device->BindResourceLayout(vertexLayout);
		device->BindVertexBuffer({ mesh->GetPositionBuffer(), mesh->GetTexCoordBuffer(), mesh->GetNormalBuffer() });
		device->BindIndexBuffer(mesh->GetIndexBuffer());
		device->UpdateBuffer(cBuffer, &constantBuffer, sizeof(ConstantBuffer));

		device->DrawIndexed(mesh->GetIndexCount(), 0, 0);

		device->Present();
	}

	device.reset();
	window.reset();
}

#pragma endregion