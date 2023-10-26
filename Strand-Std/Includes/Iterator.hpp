// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once
namespace Strand_Std
{

template<typename T>
class Iterator
{
public:
    Iterator() : _Ptr(nullptr) {}

    Iterator(T* ptr) : _Ptr(ptr) {}

    Iterator(const Iterator& other) : _Ptr(other._Ptr) {}

    Iterator& operator=(const Iterator& other)
    {
        _Ptr = other._Ptr;
        return *this;
    }

    Iterator(Iterator&& other) noexcept: _Ptr(other._Ptr) { other._Ptr = nullptr; }

    Iterator& operator=(Iterator&& other) noexcept
    {
        _Ptr = other._Ptr;
        other._Ptr = nullptr;
        return *this;
    }

    FORCEINLINE T* operator->() const noexcept { return _Ptr; }

    FORCEINLINE T& operator*() const noexcept { return *_Ptr; }

    FORCEINLINE operator T*() const noexcept { return _Ptr; }

    FORCEINLINE bool operator==(const Iterator& other) const noexcept { return _Ptr == other._Ptr; }

    FORCEINLINE bool operator!=(const Iterator& other) const noexcept { return _Ptr != other._Ptr; }

    FORCEINLINE bool operator<(const Iterator& other) const noexcept { return _Ptr < other._Ptr; }

    FORCEINLINE bool operator>(const Iterator& other) const noexcept { return _Ptr > other._Ptr; }

    FORCEINLINE bool operator<=(const Iterator& other) const noexcept { return _Ptr <= other._Ptr; }

    FORCEINLINE bool operator>=(const Iterator& other) const noexcept { return _Ptr >= other._Ptr; }

    FORCEINLINE Iterator& operator++() noexcept
    {
        ++_Ptr;
        return *this;
    }

    FORCEINLINE Iterator& operator--() noexcept
    {
        --_Ptr;
        return *this;
    }

    FORCEINLINE Iterator operator++(int) noexcept
    {
        Iterator temp = *this;
        ++_Ptr;
        return temp;
    }

    FORCEINLINE Iterator operator--(int) noexcept
    {
        Iterator temp = *this;
        --_Ptr;
        return temp;
    }

    FORCEINLINE Iterator& operator+=(int value) noexcept
    {
        _Ptr += value;
        return *this;
    }

    FORCEINLINE Iterator& operator-=(int value) noexcept
    {
        _Ptr -= value;
        return *this;
    }

    FORCEINLINE Iterator operator+(int value) const noexcept { return Iterator(_Ptr + value); }

    FORCEINLINE Iterator operator-(int value) const noexcept { return Iterator(_Ptr - value); }

    FORCEINLINE int operator-(const Iterator& other) const noexcept { return _Ptr - other._Ptr; }

    FORCEINLINE T& operator[](int index) const noexcept { return _Ptr[index]; }

    FORCEINLINE T* Get() const noexcept { return _Ptr; }

    FORCEINLINE bool IsValid() const noexcept { return _Ptr != nullptr; }

    explicit operator bool() const noexcept { return IsValid(); }

private:
    T* _Ptr = nullptr;
};

} // Strand_Std
