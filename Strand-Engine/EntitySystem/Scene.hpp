// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <EntitySystem/Entity.hpp>

namespace Strand
{

class Scene
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

private:
    std::vector<Entity*> Entities_;
};

} // Strand
