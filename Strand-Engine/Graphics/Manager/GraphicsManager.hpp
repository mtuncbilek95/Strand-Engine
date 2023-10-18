// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Singleton.hpp>
#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
namespace Strand
{
// @brief GraphicsManager class to create graphics device and manage it.
class STRAND_API GraphicsManager final : public Singleton<GraphicsManager>
{
public:
    GraphicsManager(){
        if(GraphicsDevice_ == nullptr)
            GraphicsDevice_ = std::make_shared<GraphicsDevice>();
    };
    ~GraphicsManager() = default;

    std::shared_ptr<GraphicsDevice> GetGraphicsDevice() const { return GraphicsDevice_; }
private:
    std::shared_ptr<GraphicsDevice> GraphicsDevice_;
};

} // Strand
