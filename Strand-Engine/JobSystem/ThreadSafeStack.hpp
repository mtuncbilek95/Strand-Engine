// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

// @brief Templated thread safe Stack Array
template<typename T, size_t N>
class ThreadSafeStack
{
public:
    ThreadSafeStack() : Head_(0), Tail_(0)
    {}

    FORCEINLINE bool Push(const T& value)
    {
        bool result = false;
        MutexLock_.lock();

        size_t next = (Head_ + 1) % N;
        if(next != Tail_) {
            Array_[Head_] = value;
            Head_ = next;
            result = true;
        }

        MutexLock_.unlock();
        return result;
    }

    FORCEINLINE bool Pop(T& item)
    {
        bool result = false;
        MutexLock_.lock();

        if(Tail_ != Head_) {
            item = Array_[Tail_];
            Tail_ = (Tail_ + 1) % N;
            result = true;
        }

        MutexLock_.unlock();
        return result;
    }

    FORCEINLINE bool IsEmpty() const
    {
        return Head_ == Tail_;
    }

    FORCEINLINE bool IsFull() const
    {
        return (Head_ + 1) % N == Tail_;
    }

    FORCEINLINE size_t Size() const
    {
        return (Head_ - Tail_ + N) % N;
    }

    FORCEINLINE size_t Capacity() const
    {
        return N;
    }

    FORCEINLINE T& operator[](size_t index)
    {
        return Array_[index];
    }

private:
    T Array_[N];
    size_t Head_;
    size_t Tail_;
    std::mutex MutexLock_;
};

} // Strand
