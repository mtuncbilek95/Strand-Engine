// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <EntitySystem/Component.hpp>

namespace Strand
{

class Entity
{
public:
    Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    virtual ~Entity() = default;

    void Start()
    {
        for(auto& component : Components_)
        {
            component->Start();
        }
    }

    void Update(float deltaTime)
    {
        for(auto& component : Components_)
        {
            component->Update(deltaTime);
        }
    }

    void Stop()
    {
        for(auto& component : Components_)
        {
            component->Stop();
        }
    }

    template<typename T, typename... Args>
    T* RegisterComponent(Args&&... args)
    {
        T* component = new T(args...);
        component->SetOwner(this);
        Components_.push_back(component);
        return component;
    }

    void RemoveAllComponents()
    {
        for(auto& component : Components_)
        {
            delete component;
        }
        Components_.clear();
    }

private:
    std::vector<Component*> Components_;
};

} // Strand
