#include "D3D11Swapchain.h"

#include <Runtime/D3D11/Texture/D3D11TextureUtils.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>

namespace Strand
{
	D3D11Swapchain::D3D11Swapchain(const SwapchainDesc& desc, ID3D11Device* pDevice) : Swapchain(desc)
	{
		mD3D11Device = pDevice;
		mD3D11Device->GetImmediateContext(&mD3D11Context);

		DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
		swapchainDesc.BufferCount = desc.BufferCount;
		swapchainDesc.BufferDesc.Width = desc.pWindow->GetWindowSize().x;
		swapchainDesc.BufferDesc.Height = desc.pWindow->GetWindowSize().y;
		swapchainDesc.BufferDesc.Format = D3D11TextureUtils::GetDXTextureFormat(desc.ColorFormat);
		swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.OutputWindow = desc.pWindow->GetWindowNativeHandle();
		swapchainDesc.SampleDesc.Count = static_cast<uint32>(desc.MultisampleCount);
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
		swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		switch (desc.pWindow->GetWindowMode())
		{
		case WindowMode::Windowed:
			swapchainDesc.Windowed = TRUE;
			break;
		case WindowMode::Borderless:
			swapchainDesc.Windowed = TRUE;
			break;
		case WindowMode::Fullscreen:
			swapchainDesc.Windowed = FALSE;
			break;
		}

		DEV_ASSERT(SUCCEEDED(pDevice->QueryInterface(__uuidof(IDXGIDevice), &mDXGIDevice)), "D3D11Swapchain", "Failed to get D3D11Device as DXGIDevice");
		DEV_ASSERT(SUCCEEDED(mDXGIDevice->GetParent(__uuidof(IDXGIAdapter), &mAdapter)), "D3D11Swapchain", "Failed to get DXGIDevice parent DXGIAdapter");
		DEV_ASSERT(SUCCEEDED(mAdapter->GetParent(__uuidof(IDXGIFactory), &mFactory)), "D3D11Swapchain", "Failed to get DXGIAdapter parent DXGIFactory");
		DEV_ASSERT(SUCCEEDED(mFactory->CreateSwapChain(pDevice, &swapchainDesc, &mSwapchain)), "D3D11Swapchain", "Failed to create DXGISwapchain");

		DXGI_ADAPTER_DESC adapterDesc = {};
		mAdapter->GetDesc(&adapterDesc);
		DEV_LOG(SE_WARNING, "Presented Swapchain with adapter: %S.\nIf there is a problem with this adapter, please check ID3D11Swapchain.",
			adapterDesc.Description);

		DEV_LOG(SE_VERBOSE, "Created DXGISwapchain");

		// Create swapchain render target
		ComPtr<ID3D11Texture2D> backBuffer;
		DEV_ASSERT(SUCCEEDED(mSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer)), "D3D11Swapchain", "Failed to get Backbuffer");

		D3D11_TEXTURE2D_DESC backBufferDesc = {};
		backBuffer->GetDesc(&backBufferDesc);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
		renderTargetViewDesc.Format = swapchainDesc.BufferDesc.Format;
		renderTargetViewDesc.ViewDimension = swapchainDesc.SampleDesc.Count > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateRenderTargetView(backBuffer.Get(), &renderTargetViewDesc, &mRenderTarget)), "D3D11Swapchain",
			"Failed to create DXGISwapchain render target");

		DEV_LOG(SE_VERBOSE, "Created Render Target");

		// Create swapchain depth stencil
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = swapchainDesc.BufferDesc.Width;
		depthStencilDesc.Height = swapchainDesc.BufferDesc.Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = D3D11TextureUtils::GetDXTextureFormat(desc.DepthFormat);
		depthStencilDesc.SampleDesc.Count = swapchainDesc.SampleDesc.Count;
		depthStencilDesc.SampleDesc.Quality = swapchainDesc.SampleDesc.Quality;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthTexture)), "D3D11Swapchain",
			"Failed to create DXGISwapchain depth stencil");

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = depthStencilDesc.Format;
		depthStencilViewDesc.ViewDimension = swapchainDesc.SampleDesc.Count > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateDepthStencilView(mDepthTexture.Get(), &depthStencilViewDesc, &mDepthStencil)), "D3D11Swapchain",
			"Failed to create DXGISwapchain depth stencil view");
	}

	void D3D11Swapchain::Bind()
	{
		mD3D11Context->OMSetRenderTargets(1, mRenderTarget.GetAddressOf(), mDepthStencil.Get());

		D3D11_VIEWPORT viewport;
		viewport.Width = (float)GetWindow()->GetWindowSize().x;
		viewport.Height = (float)GetWindow()->GetWindowSize().y;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		mD3D11Context->RSSetViewports(1, &viewport);
	}

	void D3D11Swapchain::ClearColor(const Vector4f& color)
	{
		float clearColor[4] = { color.x, color.y, color.z, color.w };
		mD3D11Context->ClearRenderTargetView(mRenderTarget.Get(), clearColor);
		mD3D11Context->ClearDepthStencilView(mDepthStencil.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3D11Swapchain::Present()
	{
		switch (GetPresentMode())
		{
		case PresentMode::Immediate:
		{
			mSwapchain->Present(0, 0);
			break;
		}
		case PresentMode::VsyncImmediate:
		{
			mSwapchain->Present(1, DXGI_FEATURE_PRESENT_ALLOW_TEARING);
			break;
		}
		case PresentMode::VsyncQueued:
		{
			mSwapchain->Present(1, 0);
			break;
		}
		}
	}

	void D3D11Swapchain::Resize(Vector2u newSize)
	{
		mRenderTarget.Reset();

		// Get current swapchain description
		DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
		mSwapchain->GetDesc(&swapchainDesc);
		// Resize swapchain
		DEV_ASSERT(SUCCEEDED(mSwapchain->ResizeBuffers(swapchainDesc.BufferCount, newSize.x, newSize.y, swapchainDesc.BufferDesc.Format,
			swapchainDesc.Flags)), "D3D11Swapchain", "Failed to resize DXGISwapchain");
		DEV_LOG(SE_VERBOSE, "Resized Swapchain to size: { %d, %d }", newSize.x, newSize.y);

		// Create swapchain render target
		ComPtr<ID3D11Texture2D> backBuffer;
		DEV_ASSERT(SUCCEEDED(mSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer)), "D3D11Swapchain", "Failed to get Backbuffer");

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
		renderTargetViewDesc.Format = swapchainDesc.BufferDesc.Format;
		renderTargetViewDesc.ViewDimension = swapchainDesc.SampleDesc.Count > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateRenderTargetView(backBuffer.Get(), &renderTargetViewDesc, &mRenderTarget)), "D3D11Swapchain",
			"Failed to create DXGISwapchain render target");

		DEV_LOG(SE_VERBOSE, "Created Render Target for resized Swapchain");

		mDepthTexture.Reset();

		// Create swapchain depth stencil
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = newSize.x;
		depthStencilDesc.Height = newSize.y;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = D3D11TextureUtils::GetDXTextureFormat(GetDepthFormat());
		depthStencilDesc.SampleDesc.Count = swapchainDesc.SampleDesc.Count;
		depthStencilDesc.SampleDesc.Quality = swapchainDesc.SampleDesc.Quality;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthTexture)), "D3D11Swapchain",
			"Failed to create DXGISwapchain depth stencil");

		mDepthStencil.Reset();

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = depthStencilDesc.Format;
		depthStencilViewDesc.ViewDimension = swapchainDesc.SampleDesc.Count > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		DEV_ASSERT(SUCCEEDED(mD3D11Device->CreateDepthStencilView(mDepthTexture.Get(), &depthStencilViewDesc, &mDepthStencil)), "D3D11Swapchain",
			"Failed to create DXGISwapchain depth stencil view");

		DEV_LOG(SE_VERBOSE, "Created Depth Stencil for resized Swapchain");

	}
}
