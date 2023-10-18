// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class Mesh;
class Scene;
class Texture;

class ResourceImporter
{
public:
    ResourceImporter() = delete;
    ~ResourceImporter() = delete;

    static void ReadStaticMeshFile(const String& filePath, SharedHeap<Mesh> mesh);
    static void ReadTextureFile(const String& filePath, SharedHeap<Texture> texture);
};

} // Strand
