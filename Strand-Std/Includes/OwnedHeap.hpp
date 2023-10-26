// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include "Core.hpp"

namespace Strand_Std
{

template<typename _Ty>
class OwnedHeap
{
    using _Type = _Ty;
public:
    OwnedHeap(_Type* ptr = nullptr) : _Ptr(ptr) {}

    ~OwnedHeap() { delete _Ptr; }

    OwnedHeap(const OwnedHeap&) = delete;
    OwnedHeap& operator=(const OwnedHeap&) = delete;

    OwnedHeap(OwnedHeap&& other) noexcept: _Ptr(other._Ptr) { other._Ptr = nullptr; }

    OwnedHeap& operator=(OwnedHeap&& other) noexcept
    {
        if(this != &other)
        {
            delete _Ptr;
            _Ptr = other._Ptr;
            other._Ptr = nullptr;
        }
        return *this;
    }

    FORCEINLINE _Type* operator->() const noexcept { return _Ptr; }

    FORCEINLINE _Type& operator*() const noexcept { return *_Ptr; }

    FORCEINLINE operator _Type*() const noexcept { return _Ptr; }

    NODISCARD_SMART_PTR_GET FORCEINLINE _Type* Get() const noexcept { return _Ptr; }

    FORCEINLINE void Reset(_Type* ptr = nullptr) noexcept
    {
        if(_Ptr != ptr)
        {
            delete _Ptr;
            _Ptr = ptr;
        }
    }

    FORCEINLINE _Type* Release() noexcept
    {
        _Type* ptr = _Ptr;
        _Ptr = nullptr;
        return ptr;
    }

    FORCEINLINE bool IsValid() const noexcept { return _Ptr != nullptr; }

    explicit operator bool() const noexcept { return IsValid(); }

private:
    _Type* _Ptr = nullptr;
};

template<typename T, typename... Args, EnableIf<!IsArray_V<T>, int> = 0>
NODISCARD_SMART_PTR_ALLOC constexpr OwnedHeap<T> CreateOwnedHeap(Args&& ... args)
{
    return OwnedHeap<T>(new T(args)...);
}

} // Strand_Std
