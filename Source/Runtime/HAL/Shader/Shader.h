#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/HAL/Device/GraphicsDeviceObject.h>

#include <Runtime/HAL/Shader/ShaderDesc.h>

namespace Strand
{
	class RUNTIME_API Shader : public GraphicsDeviceObject
	{
	public:
		Shader(const ShaderDesc& desc) : mShaderName(desc.ShaderName), mEntryName(desc.EntryName), 
			mShaderModel(desc.ShaderModel), mType(desc.Type), mSourceCode(desc.Source)
		{
		}
		~Shader() = default;

		String GetShaderName() const noexcept { return mShaderName; }
		String GetEntryName() const noexcept { return mEntryName; }
		String GetShaderModel() const noexcept { return mShaderModel; }
		ShaderType GetShaderType() const noexcept { return mType; }

		virtual void* GetDataPointer() noexcept = 0;
		virtual uint64 GetDataSize() noexcept = 0;

		FORCEINLINE GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Shader; }

		virtual void OnShutdown() override {};

	private:
		String mShaderName;
		String mEntryName;
		String mShaderModel;
		ShaderType mType;
		String mSourceCode;
	};
}
