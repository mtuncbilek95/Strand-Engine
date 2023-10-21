// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class DeviceObject;

struct STRAND_API PipelineResourceDesc
{
    ArrayList<SharedHeap<DeviceObject>> TextureViews;
    ArrayList<SharedHeap<DeviceObject>> BufferViews;
    ArrayList<SharedHeap<DeviceObject>> Samplers;
};

} // Strand
