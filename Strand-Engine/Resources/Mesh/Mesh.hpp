// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class GraphicsTextureView;
class Material;

enum class MeshType
{
    Static,
    Skeletal,
    Unknown
};

enum class TextureType
{
    BaseColor,
    Normal,
    Metallic,
    Roughness,
    AmbientOcclusion,
    Emissive,
    Height,
    Unknown
};

struct Texture
{
    TextureType Type;
    GraphicsTextureView* TextureView;
};


struct Vertex
{
    XMVECTOR Position;
    XMVECTOR Color;
};

struct BasicMeshDesc
{
    std::vector<Vertex> Vertices;
    std::vector<uint16_t> Indices;
    std::vector<Material*> Materials;
    std::vector<Texture*> Textures;
};

struct SkeletalMeshDesc
{
    BasicMeshDesc BasicMeshDesc;
    std::vector<std::string> BoneNames;
};

class Material;

//
class STRAND_API Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    [[nodiscard]] std::vector<Vertex>& GetVertices() { return Desc_.Vertices; }
    [[nodiscard]] std::vector<uint16_t>& GetIndices() { return Desc_.Indices; }
    [[nodiscard]] std::vector<Texture*>& GetTextures() { return Desc_.Textures; }
    [[nodiscard]] std::vector<Material*>& GetMaterials() { return Desc_.Materials; }

    void SetType(MeshType type) { Type_ = type; }
    [[nodiscard]] MeshType GetType() const { return Type_; }
private:
    BasicMeshDesc Desc_;
    MeshType Type_;
};

} // Strand
