#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

#include <Runtime/HAL/Sampler/Sampler.h>
#include <Runtime/HAL/Shader/Shader.h>
#include <Runtime/Resource/ShaderLoader/ShaderLoader.h>
#include <Runtime/HAL/Pipeline/Pipeline.h>

#include <Runtime/Resource/Camera/CameraManager.h>
#include <Runtime/Resource/Camera/FreeLookCamera.h>

#include <Runtime/TestObjects/DamagedHelmet.h>

using namespace Strand;
void TestGraphics();

int main()
{
	TestGraphics();
	return 0;
}

#pragma region "TestGraphics"

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

	SharedPtr<DamagedHelmet> testObject = std::make_shared<DamagedHelmet>();

	auto camera = CameraManager::GetInstance().CreateCamera(CameraType::FreeLook);

	testObject->Start();

	while (window->ShouldClose())
	{
		window->PollMessages();
		camera->Update(0);
		camera->UpdateInput(0);
		device->BindRenderPass();
		device->BindPipeline(pipeline);

		device->ClearColor({ 0.1f, 0.2f, 0.3f, 1.0f });
		testObject->Update();
		device->Present();
	}

	testObject->Stop();

	device.reset();
	window.reset();
}

#pragma endregion