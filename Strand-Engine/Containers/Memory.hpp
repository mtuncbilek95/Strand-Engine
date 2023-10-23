// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <memory>

/*
 * When the time comes, there will be a custom library.
 */

namespace Strand
{

template<typename T>
using SharedHeap = std::shared_ptr<T>;

template<typename T>
using OwnedHeap = std::unique_ptr<T>;

template<typename T, typename... Args>
SharedHeap<T> MakeShared(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
OwnedHeap<T> MakeUnique(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
SharedHeap<T> DynamicCast(const SharedHeap<T>& ptr)
{
    return std::dynamic_pointer_cast<T>(ptr);
}

template<typename T>
SharedHeap<T> StaticCast(const SharedHeap<T>& ptr)
{
    return std::static_pointer_cast<T>(ptr);
}

template<typename T>
SharedHeap<T> ConstCast(const SharedHeap<T>& ptr)
{
    return std::const_pointer_cast<T>(ptr);
}

template<typename T>
SharedHeap<T> ReinterpretCast(const SharedHeap<T>& ptr)
{
    return std::reinterpret_pointer_cast<T>(ptr);
}

template<typename T>
using EnableShared = std::enable_shared_from_this<T>;


} // Strand