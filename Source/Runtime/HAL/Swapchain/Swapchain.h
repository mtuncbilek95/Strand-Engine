#pragma once

#include <Runtime/HAL/Device/GraphicsDeviceObject.h>
#include <Runtime/HAL/Swapchain/SwapchainDesc.h>

namespace Strand
{
	class RUNTIME_API Swapchain : public GraphicsDeviceObject
	{
	public:
		Swapchain(const SwapchainDesc& desc) : mBufferCount(desc.BufferCount), mMultiSampleCount(desc.MultisampleCount),
			mColorFormat(desc.ColorFormat), mDepthFormat(desc.DepthFormat), mWindow(desc.pWindow), mPresentMode(desc.PresentMode)
		{
		}
		virtual ~Swapchain() override = default;

		FORCEINLINE byte GetBufferCount() const { return mBufferCount; }
		FORCEINLINE SampleCount GetMultiSampleCount() const { return mMultiSampleCount; }
		FORCEINLINE TextureFormat GetColorFormat() const { return mColorFormat; }
		FORCEINLINE TextureFormat GetDepthFormat() const { return mDepthFormat; }
		FORCEINLINE SharedPtr<Window> GetWindow() const { return mWindow; }
		FORCEINLINE PresentMode GetPresentMode() const { return mPresentMode; }

		virtual void ClearColor(const Vector4f& color) = 0;
		virtual void Present() = 0;
		virtual void Resize(Vector2u newSize) = 0;

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Swapchain; }

		virtual void OnShutdown() override {};

	private:
		byte mBufferCount;
		SampleCount mMultiSampleCount;
		TextureFormat mColorFormat;
		TextureFormat mDepthFormat;
		SharedPtr<Window> mWindow;
		PresentMode mPresentMode;


	};
}
