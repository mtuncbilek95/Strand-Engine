// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

#include <Resources/Texture/TextureDesc.hpp>
#include <Graphics/Resources/GraphicsTextureView/GraphicsTextureView.hpp>

namespace Strand
{
// @brief Texture class to create textures and manage them.
class STRAND_API Texture
{
public:
    Texture() = default;
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;
    ~Texture() = default;

    void AllocateTexture();

    GraphicsTextureView* GetTextureView() const { return TextureView_; }
    TextureDesc& GetTextureDesc() { return TextureDesc_; }

private:
    GraphicsTextureView* TextureView_ = nullptr;
    TextureDesc TextureDesc_;
};

} // Strand
