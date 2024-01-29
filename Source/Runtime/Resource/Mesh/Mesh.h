#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Buffer/GraphicsBuffer.h>

namespace Strand
{
	class RUNTIME_API Mesh
	{
		friend class MeshLoader;
	public:
		Mesh() = default;
		~Mesh() = default;

		void AllocateBuffers();
		uint16 GetIndexCount() const { return mIndices.size(); }


		SharedPtr<GraphicsBuffer> GetPositionBuffer() const { return mPositionBuffer; }
		SharedPtr<GraphicsBuffer> GetNormalBuffer() const { return mNormalBuffer; }
		SharedPtr<GraphicsBuffer> GetTexCoordBuffer() const { return mTexCoordBuffer; }
		SharedPtr<GraphicsBuffer> GetTangentBuffer() const { return mTangentBuffer; }
		SharedPtr<GraphicsBuffer> GetBitangentBuffer() const { return mBitangentBuffer; }
		SharedPtr<GraphicsBuffer> GetColorBuffer() const { return mColorBuffer; }
		SharedPtr<GraphicsBuffer> GetIndexBuffer() const { return mIndexBuffer; }

	private:
		ArrayList<Vector3f> mPositions;
		ArrayList<Vector3f> mNormals;
		ArrayList<Vector2f> mTexCoords;
		ArrayList<Vector3f> mTangents;
		ArrayList<Vector3f> mBitangents;
		ArrayList<Vector4f> mColors;
		ArrayList<uint16> mIndices;

		SharedPtr<GraphicsBuffer> mPositionBuffer;
		SharedPtr<GraphicsBuffer> mNormalBuffer;
		SharedPtr<GraphicsBuffer> mTexCoordBuffer;
		SharedPtr<GraphicsBuffer> mTangentBuffer;
		SharedPtr<GraphicsBuffer> mBitangentBuffer;
		SharedPtr<GraphicsBuffer> mColorBuffer;
		SharedPtr<GraphicsBuffer> mIndexBuffer;

	};
}
