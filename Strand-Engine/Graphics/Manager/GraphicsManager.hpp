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
        if(m_GraphicsDevice == nullptr)
            m_GraphicsDevice = new GraphicsDevice();
    };
    ~GraphicsManager() = default;

    GraphicsDevice* GetGraphicsDevice() const { return m_GraphicsDevice; }
private:
    GraphicsDevice* m_GraphicsDevice;
};

} // Strand
