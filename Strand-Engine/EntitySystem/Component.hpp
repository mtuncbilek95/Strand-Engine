// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once
namespace Strand
{

class Component
{
public:
    Component() = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    virtual ~Component() = default;
};

} // Strand
