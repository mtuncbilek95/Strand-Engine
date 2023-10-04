// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class Mesh;
class Scene;

class MeshLoader
{
public:
    MeshLoader() = delete;
    ~MeshLoader() = delete;

    static bool ReadStaticMeshFile(const std::string& filePath, Mesh* mesh);
    static bool ReadSkeletalMeshFile(const std::string& filePath, Mesh* mesh);
    static bool ReadSceneFile(const std::string& filePath, Scene* mesh);
};

} // Strand
