#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Command/CommandBuffer.h>

#include <d3d11.h>
#include <wrl.h>
using namespace Microsoft::WRL;

namespace Strand
{
	class RUNTIME_API D3D11CommandBuffer : public CommandBuffer
	{
	public:
		D3D11CommandBuffer(ID3D11Device* pDevice);
		~D3D11CommandBuffer() override = default;

		void InitContext(ID3D11Device* pDevice);
		virtual void BindPipeline(const SharedPtr<Pipeline>& pipeline) override;
		virtual void BindViewport() override;
		virtual void BindVertexBuffer(const SharedPtr<GraphicsBuffer>& vertexBuffer) override;
		virtual void BindIndexBuffer(const SharedPtr<GraphicsBuffer>& indexBuffer) override;
		virtual void BindResourceLayout(const SharedPtr<ResourceLayout>& resourceLayout) override;
		virtual void DrawIndex(const uint32 indexCount, const uint32 indexOffset, const uint32 vertexOffset) override;
		virtual void Draw(const uint32 vertexCount, const uint32 vertexOffset) override;
		virtual void DrawInstanced(const uint32 vertexCount, const uint32 vertexOffset, const uint32 instanceCount, const uint32 instanceOffset) override;
		virtual void ClearColor(const Vector4f& color) override;
		virtual void Reset() override;

		void OnShutdown() override {};

		ComPtr<ID3D11DeviceContext>& GetDeferredContext() { return mDeferredContext; }
		ComPtr<ID3D11CommandList>& GetCommandList() { return mCommandList; }

	private:
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mImmediateContext;
		ComPtr<ID3D11DeviceContext> mDeferredContext;
		ComPtr<ID3D11CommandList> mCommandList;
	};
}
