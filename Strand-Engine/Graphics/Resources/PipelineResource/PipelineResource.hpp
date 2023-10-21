// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Graphics/GraphicsDevice/DeviceObject.hpp>

#include <Graphics/Resources/PipelineResource/PipelineResourceDesc.hpp>

namespace Strand
{
// @brief PipelineResource is a resource object that contains texture views, buffer views and samplers to bind to a pipeline.
class PipelineResource : public DeviceObject
{
public:
    PipelineResource(SharedHeap<GraphicsDevice> device, const PipelineResourceDesc& desc);
    PipelineResource(const PipelineResource&) = delete;
    PipelineResource& operator=(const PipelineResource&) = delete;
    PipelineResource& operator=(PipelineResource&&) = delete;
    PipelineResource(PipelineResource&&) = delete;
    ~PipelineResource() = default;

    DeviceObjectType GetDeviceObjectType() override { return DeviceObjectType::PIPELINE_RESOURCE; }
private:
    ArrayList<SharedHeap<DeviceObject>> TextureViews_;
    ArrayList<SharedHeap<DeviceObject>> BufferViews_;
    ArrayList<SharedHeap<DeviceObject>> Samplers_;

    bool HasTextureViews_ = false;
    bool HasBufferViews_ = false;
    bool HasSamplers_ = false;
};

} // Strand
