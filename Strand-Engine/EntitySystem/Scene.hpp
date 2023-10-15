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

    void Start(){
        for (auto& entity : Entities_)
            entity->Start();
    }

    void Update(float deltaTime){
        for (auto& entity : Entities_)
            entity->Update(deltaTime);
    }

    void Stop(){
        for (auto& entity : Entities_)
            entity->Stop();
    }

    template<typename T, typename... Args>
    requires std::derived_from<T, Entity>
    T* CreateEntity(Args&&... args)
    {
        T* entity = new T(args...);
        Entities_.push_back(entity);
        return entity;
    }

    template<typename T>
    T* GetEntity()
    {
        for (auto& entity : Entities_)
        {
            if (dynamic_cast<T*>(entity))
                return dynamic_cast<T*>(entity);
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> GetEntities()
    {
        std::vector<T*> entities;
        for (auto& entity : Entities_)
        {
            if (dynamic_cast<T*>(entity))
                entities.push_back(dynamic_cast<T*>(entity));
        }
        return entities;
    }
    
private:
    std::vector<Entity*> Entities_;
};

} // Strand
