// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once
namespace Strand
{

class Entity;

class Component
{
public:
    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    virtual ~Component() = default;

    void SetOwner(Entity* owner)
    { ComponentOwner_ = owner; }

    Entity* GetOwner() const
    { return ComponentOwner_; }

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Stop() = 0;

private:
    Entity* ComponentOwner_;
};

} // Strand
