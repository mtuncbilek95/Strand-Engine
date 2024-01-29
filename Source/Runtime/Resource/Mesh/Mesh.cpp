#include "Mesh.h"

#include <Runtime/HAL/Buffer/GraphicsBuffer.h>
#include <Runtime/HAL/Manager/GraphicsManager.h>

namespace Strand
{
	void Mesh::AllocateBuffers()
	{
		GraphicsBufferDesc vertexBufferDesc;
		vertexBufferDesc.CPUAccess = BufferCPUAccess::None;
		vertexBufferDesc.Usage = BufferUsage::VertexBuffer;
		vertexBufferDesc.ResourceUsage = ResourceUsage::Default;
		vertexBufferDesc.SizeInBytes = sizeof(Vector3f) * mPositions.size();
		vertexBufferDesc.StructureByteStride = sizeof(Vector3f);
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.InitialData = mPositions.data();

		if (mPositions.size() != 0)
			mPositionBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(vertexBufferDesc);

		vertexBufferDesc.SizeInBytes = sizeof(Vector3f) * mNormals.size();
		vertexBufferDesc.StructureByteStride = sizeof(Vector3f);
		vertexBufferDesc.InitialData = mNormals.data();

		if (mNormals.size() != 0)
			mNormalBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(vertexBufferDesc);

		vertexBufferDesc.SizeInBytes = sizeof(Vector2f) * mTexCoords.size();
		vertexBufferDesc.StructureByteStride = sizeof(Vector2f);
		vertexBufferDesc.InitialData = mTexCoords.data();

		if (mTexCoords.size() != 0)
			mTexCoordBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(vertexBufferDesc);

		vertexBufferDesc.SizeInBytes = sizeof(Vector3f) * mTangents.size();
		vertexBufferDesc.StructureByteStride = sizeof(Vector3f);
		vertexBufferDesc.InitialData = mTangents.data();

		if (mTangents.size() != 0)
			mTangentBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(vertexBufferDesc);

		vertexBufferDesc.SizeInBytes = sizeof(Vector3f) * mBitangents.size();
		vertexBufferDesc.StructureByteStride = sizeof(Vector3f);
		vertexBufferDesc.InitialData = mBitangents.data();

		if (mBitangents.size() != 0)
			mBitangentBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(vertexBufferDesc);

		GraphicsBufferDesc indexBufferDesc;
		indexBufferDesc.CPUAccess = BufferCPUAccess::None;
		indexBufferDesc.Usage = BufferUsage::IndexBuffer;
		indexBufferDesc.ResourceUsage = ResourceUsage::Default;
		indexBufferDesc.SizeInBytes = sizeof(uint16) * mIndices.size();
		indexBufferDesc.StructureByteStride = sizeof(uint16);
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.InitialData = mIndices.data();

		if (mIndices.size() != 0)
			mIndexBuffer = GraphicsManager::GetInstance().GetDevice()->CreateGraphicsBuffer(indexBufferDesc);
	}
}
