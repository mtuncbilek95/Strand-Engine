// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <mutex>

namespace Strand
{

template <typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        std::lock_guard<std::mutex> lock(Mutex_);
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    static std::mutex Mutex_;
};

template <typename T>
std::mutex Singleton<T>::Mutex_;

} // Strand
