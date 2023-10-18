// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <EntitySystem/Entity.hpp>

namespace Strand
{
// @brief Scene class to create entities and manage them.
class STRAND_API Scene
{
public:
    Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    virtual ~Scene() = default;

    void Start()
    {
        for(auto& entity: Entities_)
            entity->Start();
    }

    void Update(float deltaTime)
    {
        for(auto& entity: Entities_)
            entity->Update(deltaTime);
    }

    void Stop()
    {
        for(auto& entity: Entities_)
            entity->Stop();
    }

    template<typename T, typename... Args>
    requires std::derived_from<T, Entity>
    std::shared_ptr<T> CreateEntity(Args&& ... args)
    {
        auto entity = std::make_shared<T>(args...);
        Entities_.push_back(entity);
        return entity;
    }

    template<typename T>
    std::shared_ptr<T> GetEntity()
    {
        for(auto& entity: Entities_) {
            if(auto castedEntity = std::dynamic_pointer_cast<T>(entity)) {
                return castedEntity;
            }
        }
        return nullptr;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> GetEntities()
    {
        std::vector<std::shared_ptr<T>> entities;
        for(auto& entity: Entities_) {
            if(auto castedEntity = std::dynamic_pointer_cast<T>(entity)) {
                entities.push_back(castedEntity);
            }
        }
        return entities;
    }

private:
    std::vector<std::shared_ptr<Entity>> Entities_;
};

} // Strand
