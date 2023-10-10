// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class Component;

class Entity
{
public:
    Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    virtual ~Entity() = default;

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

private:
    std::vector<Component*> Components_;
};

} // Strand
