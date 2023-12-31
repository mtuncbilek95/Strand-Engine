// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class Entity;
// @brief Component class to create components and manage them.
class STRAND_API Component
{
public:
    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    virtual ~Component() = default;

    void SetOwner(SharedHeap<Entity> owner)
    { ComponentOwner_ = owner; }

    SharedHeap<Entity> GetOwner() const
    { return ComponentOwner_; }

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Stop() = 0;

private:
    SharedHeap<Entity> ComponentOwner_;
};

} // Strand
