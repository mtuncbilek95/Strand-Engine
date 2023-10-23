// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <RHI/GraphicsDevice/DeviceObject.hpp>
#include <RHI/Shader/ShaderDesc.hpp>

namespace Strand
{

class ENGINE_API Shader : public DeviceObject
{
public:
    Shader(const ShaderDesc& desc);
    Shader(const Shader& other) noexcept = delete;
    Shader(Shader&& other) noexcept = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) noexcept = delete;
    ~Shader() override = default;
};

} // Strand
