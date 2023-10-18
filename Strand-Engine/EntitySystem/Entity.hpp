// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <EntitySystem/Component.hpp>

namespace Strand
{
// @brief Entity class to create components and manage them.
class STRAND_API Entity
{
public:
    Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    virtual ~Entity() = default;

    void Start()
    {
        for(auto& component: Components_) {
            component->Start();
        }
    }

    void Update(float deltaTime)
    {
        for(auto& component: Components_) {
            component->Update(deltaTime);
        }
    }

    void Stop()
    {
        for(auto& component: Components_) {
            component->Stop();
        }
    }

    template<typename T, typename... Args>
    requires std::derived_from<T, Component>
    std::shared_ptr<T> RegisterComponent(Args&& ... args)
    {
        auto component = std::make_shared<T>(args...);
        Components_.push_back(component);
        return component;
    }

    void RemoveAllComponents()
    {
        for(auto& component: Components_) {
            component->Stop();
            component.reset();
        }

        Components_.clear();
    }

    template<typename T>
    std::shared_ptr<Component> GetComponentByType()
    {
        for(auto& component: Components_) {
            if(auto castedComponent = std::dynamic_pointer_cast<T>(component))
                return castedComponent;
        }
        return nullptr;
    }

    template<typename T>
    std::vector<std::shared_ptr<Component>> GetAllComponentsByType()
    {
        std::vector<T*> components;
        for(auto& component: Components_) {
            if(auto castedComponent = std::dynamic_pointer_cast<T>(component))
                components.push_back(castedComponent);
        }
        return components;
    }

private:
    std::vector<std::shared_ptr<Component>> Components_;
};

} // Strand