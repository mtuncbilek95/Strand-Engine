// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

namespace Strand_Std
{

class EXPORT_STRAND_STD Memory
{
public:
    Memory() = delete;
    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory(Memory&&) = delete;
    Memory& operator=(Memory&&) = delete;
    ~Memory() = delete;

#if defined(STRAND_PLATFORM_WINDOWS)

    static void Copy(void* __restrict destination, const void* __restrict source, unsigned int targetSize)
    {
        const char* __restrict src = static_cast<const char*>(source);
        char* __restrict dst = static_cast<char*>(destination);

        for(unsigned int i = 0; i < targetSize; ++i) {
            dst[i] = src[i];
        }
    }

    static void Check(void* __restrict destination, const void* __restrict source, unsigned int targetSize)
    {
        const char* __restrict src = static_cast<const char*>(source);
        char* __restrict dst = static_cast<char*>(destination);

        for(unsigned int i = 0; i < targetSize; ++i) {
            if(dst[i] != src[i]) {
                __debugbreak();
            }
        }
    }

    static void Set(void* __restrict destination, unsigned char value, unsigned int targetSize)
    {
        char* __restrict dst = static_cast<char*>(destination);

        for(unsigned int i = 0; i < targetSize; ++i) {
            dst[i] = value;
        }
    }

    static void CopySafe(void* __restrict destination, unsigned int destSize, const void* __restrict source, unsigned int sourceSize)
    {
        const char* __restrict src = static_cast<const char*>(source);
        char* __restrict dst = static_cast<char*>(destination);

        unsigned int size = destSize < sourceSize ? destSize : sourceSize;

        for(unsigned int i = 0; i < size; ++i) {
            dst[i] = src[i];
        }
    }

    static void CheckSafe(void* __restrict destination, unsigned int destSize, const void* __restrict source, unsigned int sourceSize)
    {
        const char* __restrict src = static_cast<const char*>(source);
        char* __restrict dst = static_cast<char*>(destination);

        unsigned int size = destSize < sourceSize ? destSize : sourceSize;

        for(unsigned int i = 0; i < size; ++i) {
            if(dst[i] != src[i]) {
                __debugbreak();
            }
        }
    }

    static void SetSafe(void* __restrict destination, unsigned int destSize, unsigned char value, unsigned int targetSize)
    {
        char* __restrict dst = static_cast<char*>(destination);

        unsigned int size = destSize < targetSize ? destSize : targetSize;

        for(unsigned int i = 0; i < size; ++i) {
            dst[i] = value;
        }
    }

#elif defined(STRAND_PLATFORM_LINUX)
    static void Copy(void* destination, __restrict__ const void* __restrict__ source, unsigned int size);
#elif defined(STRAND_PLATFORM_MACOS)
    static void Copy(void* destination, const void* source, unsigned int size);
#endif
};

} // Strand_Std
