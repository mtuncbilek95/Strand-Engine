// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Singleton.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
namespace Strand
{

class STRAND_API GraphicsManager final : public Singleton<GraphicsManager>
{
public:
    GraphicsManager(){
        if(GraphicsDevice_ == nullptr)
            GraphicsDevice_ = new GraphicsDevice();
    };
    ~GraphicsManager() = default;

    GraphicsDevice* GetGraphicsDevice() const { return GraphicsDevice_; }
private:
    GraphicsDevice* GraphicsDevice_;
};

} // Strand
