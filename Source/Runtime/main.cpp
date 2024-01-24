#include <Runtime/HAL/Manager/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/HAL/Swapchain/Swapchain.h>

using namespace Strand;

int main()
{
	WindowDesc windowDesc
	{
		.WindowSize = {1280, 720 },
		.WindowPosition = { 500, 500 },
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
		.pWindow = window,
		.PresentMode = PresentMode::VsyncQueued
	};

	SharedPtr<Swapchain> swapchain = device->CreateSwapchain(swapchainDesc);

	while (window->ShouldClose())
	{
		window->PollMessages();
		swapchain->ClearColor({ 0.2f, 0.3f, 0.5f, 1.0f });
		swapchain->Present();
	}

	device.reset();
	window.reset();

	return 0;
}
