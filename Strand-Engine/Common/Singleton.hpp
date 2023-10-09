// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

namespace Strand
{

template <typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
};

} // Strand
