#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Shader/ShaderStage.h>

namespace Strand
{
	class Pipeline;
	class GraphicsBuffer;
	class TextureView;
	class Sampler;
	class RenderPass;
	class ResourceLayout;

	class RUNTIME_API CommandBuffer : public GraphicsDeviceObject
	{
	public:
		CommandBuffer() = default;
		virtual ~CommandBuffer() override = default;

		virtual void BindPipeline(const SharedPtr<Pipeline>& pipeline) = 0;
		virtual void BindViewport(Vector2u windowSize) = 0;
		virtual void BindScissor(Vector2u windowSize) = 0;
		virtual void BindVertexBuffer(const SharedPtr<GraphicsBuffer>& vertexBuffer) = 0;
		virtual void BindIndexBuffer(const SharedPtr<GraphicsBuffer>& indexBuffer) = 0;
		virtual void BindRenderPass(const SharedPtr<RenderPass>& renderPass) = 0;
		virtual void BindResourceLayout(const SharedPtr<ResourceLayout>& resourceLayout) = 0;
		virtual void DrawIndex(const uint32 indexCount, const uint32 indexOffset, const uint32 vertexOffset) = 0;
		virtual void Draw(const uint32 vertexCount, const uint32 vertexOffset) = 0;
		virtual void DrawInstanced(const uint32 vertexCount, const uint32 vertexOffset, const uint32 instanceCount, const uint32 instanceOffset) = 0;
		virtual void ClearColor(const Vector4f& color) = 0;
		virtual void Reset() = 0;

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::CommandBuffer; }

		virtual void OnShutdown() override {};
	};
}
