#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/HAL/Swapchain/Swapchain.h>
#include <Runtime/D3D11/Device/D3D11Device.h>

#include <d3d11_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;


namespace Strand
{
	class RUNTIME_API D3D11Swapchain : public Swapchain
	{
	public:
		D3D11Swapchain(const SwapchainDesc& desc, ID3D11Device* pDevice);
		virtual ~D3D11Swapchain() override = default;

		void ClearColor(const Vector4f& color) override;
		void Present() override;
		void Resize(Vector2u newSize) override;

		void OnShutdown() override {};

		ComPtr<IDXGISwapChain>& GetSwapchain() { return mSwapchain; }
		ComPtr<ID3D11RenderTargetView>& GetRenderTarget() { return mRenderTarget; }
		ComPtr<ID3D11Texture2D>& GetDepthTexture() { return mDepthTexture; }
		ComPtr<ID3D11DepthStencilView>& GetDepthStencil() { return mDepthStencil; }
		ComPtr<IDXGIAdapter>& GetAdapter() { return mAdapter; }
		ComPtr<IDXGIFactory>& GetFactory() { return mFactory; }

	private:
		ID3D11Device* mD3D11Device;
		ComPtr<IDXGIDevice> mDXGIDevice;
		ComPtr<IDXGISwapChain> mSwapchain;
		ComPtr<IDXGIAdapter> mAdapter;
		ComPtr<IDXGIFactory> mFactory;

		ComPtr<ID3D11RenderTargetView> mRenderTarget;
		ComPtr<ID3D11Texture2D> mDepthTexture;
		ComPtr<ID3D11DepthStencilView> mDepthStencil;
	};
}
