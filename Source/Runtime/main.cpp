#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

#include <Runtime/HAL/Sampler/Sampler.h>
#include <Runtime/HAL/Shader/Shader.h>
#include <Runtime/Resource/ShaderLoader/ShaderLoader.h>

#include <Runtime/HAL/Pipeline/Pipeline.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>
#include <Runtime/HAL/Command/CommandBuffer.h>
#include <Runtime/D3D11/Device/D3D11Device.h>
#include <Runtime/D3D11/Command/D3D11CommandBuffer.h>

using namespace Strand;

struct Vertex
{
	Vector3f Position;
	Vector3f Color;
};

ArrayList<Vertex> triangle =
{
	{ {-0.5f, -0.5f, 1.0f}, {1.0f, 0.0f, 0.0f} },
	{ { 0.0f,  0.5f, 1.0f}, {0.0f, 1.0f, 0.0f} },
	{ { 0.5f, -0.5f, 1.0f}, {0.0f, 0.0f, 1.0f} }
};

ArrayList<Vertex> triangle2 =
{
	{ {-0.2f, -0.2f, 0.5f}, {1.0f, 0.0f, 0.0f} },
	{ { 0.3f,  0.8f, 0.5f}, {0.0f, 1.0f, 0.0f} },
	{ { 0.8f, -0.2f, 0.5f}, {0.0f, 0.0f, 1.0f} }
};

ArrayList<uint16> indices = { 0, 1, 2 };
ArrayList<uint16> indices2 = { 0, 1, 2 };

int main()
{
	WindowDesc windowDesc
	{
		.WindowSize = { 1920, 1080 },
		.WindowPosition = { (2560 - 1920) / 2, (1440 - 1080)/2 },
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
		.BufferCount = 1,
		.MultisampleCount = SampleCount::Sample_1,
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
			{ SemanticName::Color, TextureFormat::RGB32_Float, 0 , 0 , 0xffffffff, SlotClass::PerVertexData, 0 }
		},
		.Rasterizer = { FillMode::Solid, CullMode::Back, FaceOrdering::Clockwise, 0, 0, 0, false, false, true, true },
		.DepthStencil = { true, DepthMask::All, DepthStencilComparisonFunc::Less, false, 0xFF, 0xFF },
		.Blend = { false, true, { true, BlendType::One, BlendType::Zero, BlendOperation::Add, BlendType::One, BlendType::Zero, BlendOperation::Add, ColorMask::All } },
		.Sampler = sampler,
		.PrimitiveMode = PrimitiveMode::TriangleList
	};

	SharedPtr<Pipeline> pipeline = device->CreateGraphicsPipeline(pipelineDesc);

	GraphicsBufferDesc vBufferDesc
	{
		.Usage = BufferUsage::VertexBuffer,
		.CPUAccess = BufferCPUAccess::None,
		.ResourceUsage = ResourceUsage::Default,
		.MiscFlags = 0,
		.SizeInBytes = static_cast<uint32>(sizeof(Vertex) * triangle.size()),
		.StructureByteStride = sizeof(Vertex),
		.InitialData = triangle.data()
	};

	GraphicsBufferDesc vBufferDesc2
	{
		.Usage = BufferUsage::VertexBuffer,
		.CPUAccess = BufferCPUAccess::None,
		.ResourceUsage = ResourceUsage::Default,
		.MiscFlags = 0,
		.SizeInBytes = static_cast<uint32>(sizeof(Vertex) * triangle2.size()),
		.StructureByteStride = sizeof(Vertex),
		.InitialData = triangle2.data()
	};

	SharedPtr<GraphicsBuffer> vBuffer = device->CreateGraphicsBuffer(vBufferDesc);
	SharedPtr<GraphicsBuffer> vBuffer2 = device->CreateGraphicsBuffer(vBufferDesc2);

	GraphicsBufferDesc iBufferDesc
	{
		.Usage = BufferUsage::IndexBuffer,
		.CPUAccess = BufferCPUAccess::None,
		.ResourceUsage = ResourceUsage::Default,
		.MiscFlags = 0,
		.SizeInBytes = static_cast<uint32>(sizeof(uint16) * indices.size()),
		.StructureByteStride = sizeof(uint16),
		.InitialData = indices.data()
	};

	GraphicsBufferDesc iBufferDesc2
	{
		.Usage = BufferUsage::IndexBuffer,
		.CPUAccess = BufferCPUAccess::None,
		.ResourceUsage = ResourceUsage::Default,
		.MiscFlags = 0,
		.SizeInBytes = static_cast<uint32>(sizeof(uint16) * indices2.size()),
		.StructureByteStride = sizeof(uint16),
		.InitialData = indices2.data()
	};

	SharedPtr<GraphicsBuffer> iBuffer = device->CreateGraphicsBuffer(iBufferDesc);
	SharedPtr<GraphicsBuffer> iBuffer2 = device->CreateGraphicsBuffer(iBufferDesc2);

	SharedPtr<CommandBuffer> commandBuffer2 = device->CreateCommandBuffer();
	SharedPtr<CommandBuffer> commandBuffer = device->CreateCommandBuffer();


	while (window->ShouldClose())
	{
		window->PollMessages();

		commandBuffer->ClearColor({ 0.2f, 0.3f, 0.5f, 1.0f });
		commandBuffer->BindViewport();

		commandBuffer->BindIndexBuffer(iBuffer);
		commandBuffer->BindVertexBuffer(vBuffer);
		commandBuffer->BindPipeline(pipeline);
		commandBuffer->DrawIndex(indices.size(), 0, 0);

		commandBuffer2->BindViewport();

		commandBuffer2->BindIndexBuffer(iBuffer2);
		commandBuffer2->BindVertexBuffer(vBuffer2);
		commandBuffer2->BindPipeline(pipeline);
		commandBuffer2->DrawIndex(indices2.size(), 0, 0);

		swapchain->Present();
	}

	device.reset();
	window.reset();

	return 0;
}
