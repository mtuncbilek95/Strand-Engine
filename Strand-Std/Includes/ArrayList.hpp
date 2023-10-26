// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Core.hpp>
#include <Iterator.hpp>

namespace Strand_Std
{

template<typename T>
class ArrayList
{
public:
    ArrayList()
    {
        _Data = nullptr;
        _Size = 0;
        _Capacity = 0;
    }

    ArrayList(const ArrayList& other)
    {
        _Data = new T[other.GetCapacity()];
        _Size = other.GetSize();
        _Capacity = other.GetCapacity();

        for(unsigned int i = 0; i < _Size; i++)
        {
            _Data[i] = other._Data[i];
        }
    }

    ArrayList(ArrayList&& other) noexcept
    {
        _Data = other.GetData();
        _Size = other.GetSize();
        _Capacity = other.GetCapacity();

        other.Clear();
    }

    ArrayList& operator=(const ArrayList& other)
    {
        if(this != &other)
        {
            _Data = new T[other.GetCapacity()];
            _Size = other.GetSize();
            _Capacity = other.GetCapacity();

            for(unsigned int i = 0; i < _Size; i++)
            {
                _Data[i] = other._Data[i];
            }
        }
        return *this;
    }

    ArrayList& operator=(ArrayList&& other) noexcept
    {
        if(this != &other)
        {
            _Data = other.GetData();
            _Size = other.GetSize();
            _Capacity = other.GetCapacity();

            other.Clear();
        }
        return *this;
    }

    ~ArrayList()
    {
        delete[] _Data;
        _Data = nullptr;
        _Size = 0;
        _Capacity = 0;
    }

    void AddLast(const T& value)
    {
        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        _Data[_Size] = value;
        _Size++;
    }

    void AddLast(T&& value)
    {
        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        _Data[_Size] = value;
        value = nullptr;
        _Size++;
    }

    void AddFirst(const T& value)
    {
        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        for(unsigned int i = _Size; i > 0; i--)
        {
            _Data[i] = _Data[i - 1];
        }

        _Data[0] = value;
        _Size++;
    }

    void AddFirst(T&& value)
    {
        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        for(unsigned int i = _Size; i > 0; i--)
        {
            _Data[i] = _Data[i - 1];
        }

        _Data[0] = value;
        value = nullptr;
        _Size++;
    }

    void AddAt(const T& value, int index)
    {
#if defined (_DEBUG)
        if(index < 0 || index > _Size)
            __debugbreak();
#else
        if(index < 0 || index > _Size)
            return;
#endif

        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        for(unsigned int i = _Size; i > index; i--)
        {
            _Data[i] = _Data[i - 1];
        }

        _Data[index] = value;
        _Size++;
    }

    void AddAt(T&& value, int index)
    {
#if defined (_DEBUG)
        if(index < 0 || index > _Size)
            __debugbreak();
#else
        if(index < 0 || index > _Size)
            return;
#endif
        if(_Size == 0)
            _Resize(1);

        if(_Size == _Capacity)
            _Resize(_Capacity * 2);

        for(unsigned int i = _Size; i > index; i--)
        {
            _Data[i] = _Data[i - 1];
        }

        _Data[index] = value;
        value = nullptr;
        _Size++;
    }

    void RemoveLast()
    {
#if defined (_DEBUG)
        if(_Size == 0)
            __debugbreak();
#else
        if(_Size == 0)
            return;
#endif
        _Size--;
        if(_Size == 0)
            _Reset();
    }

    void RemoveFirst()
    {
#if defined (_DEBUG)
        if(_Size == 0)
            __debugbreak();
#else
        if(_Size == 0)
            return;
#endif
        for(unsigned int i = 0; i < _Size - 1; i++)
        {
            _Data[i] = _Data[i + 1];
        }

        _Size--;
        if(_Size == 0)
            _Reset();
    }

    void RemoveAt(int index)
    {
#if defined (_DEBUG)
        if(index < 0 || index >= _Size)
            __debugbreak();
#else
        if(index < 0 || index >= _Size)
            return;
#endif
        for(unsigned int i = index; i < _Size - 1; i++)
        {
            _Data[i] = _Data[i + 1];
        }

        _Size--;
        if(_Size == 0)
            _Reset();
    }

    void RemoveAll()
    {
        _Reset();
    }

    void Clear()
    {
        _Reset();

        _Data = nullptr;
        _Size = 0;
        _Capacity = 0;
    }

    NODISCARD const T& GetAt(int index) const { return _Data[index];}
    NODISCARD T* GetData() { return _Data;}
    NODISCARD const T& operator[](int index) const { return _Data[index]; }
    NODISCARD const T& GetLast() const { return _Data[_Size - 1]; }
    NODISCARD const T& GetFirst() const { return _Data[0]; }
    NODISCARD const T& operator*() const { return _Data; }

    NODISCARD unsigned int GetSize() const { return _Size; }
    NODISCARD unsigned int GetCapacity() const { return _Capacity; }

    NODISCARD bool IsEmpty() const { return _Size == 0; }

    NODISCARD bool IsValid() const { return _Data != nullptr; }

    NODISCARD bool operator==(const ArrayList& other) const
    {
        if(_Size != other.GetSize())
            return false;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] != other._Data[i])
                return false;
        }

        return true;
    }

    NODISCARD bool operator!=(const ArrayList& other) const
    {
        if(_Size != other.GetSize())
            return true;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] != other._Data[i])
                return true;
        }

        return false;
    }

    NODISCARD bool operator<(const ArrayList& other) const
    {
        if(_Size < other.GetSize())
            return true;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] < other._Data[i])
                return true;
        }

        return false;
    }

    NODISCARD bool operator>(const ArrayList& other) const
    {
        if(_Size > other.GetSize())
            return true;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] > other._Data[i])
                return true;
        }

        return false;
    }

    NODISCARD bool operator<=(const ArrayList& other) const
    {
        if(_Size <= other.GetSize())
            return true;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] <= other._Data[i])
                return true;
        }

        return false;
    }

    NODISCARD bool operator>=(const ArrayList& other) const
    {
        if(_Size >= other.GetSize())
            return true;

        for(unsigned int i = 0; i < _Size; i++)
        {
            if(_Data[i] >= other._Data[i])
                return true;
        }

        return false;
    }

    NODISCARD bool operator==(const T& other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] == other;
    }

    NODISCARD bool operator!=(const T& other) const
    {
        if(_Size != 1)
            return true;

        return _Data[0] != other;
    }

    NODISCARD bool operator<(const T& other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] < other;
    }

    NODISCARD bool operator>(const T& other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] > other;
    }

    NODISCARD bool operator<=(const T& other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] <= other;
    }

    NODISCARD bool operator>=(const T& other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] >= other;
    }

    NODISCARD bool operator==(const T* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] == other;
    }

    NODISCARD bool operator!=(const T* other) const
    {
        if(_Size != 1)
            return true;

        return _Data[0] != other;
    }

    NODISCARD bool operator<(const T* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] < other;
    }

    NODISCARD bool operator>(const T* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] > other;
    }

    NODISCARD bool operator<=(const T* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] <= other;
    }

    NODISCARD bool operator>=(const T* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] >= other;
    }

    NODISCARD bool operator==(const ArrayList* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] == other;
    }

    NODISCARD bool operator!=(const ArrayList* other) const
    {
        if(_Size != 1)
            return true;

        return _Data[0] != other;
    }

    NODISCARD bool operator<(const ArrayList* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] < other;
    }

    NODISCARD bool operator>(const ArrayList* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] > other;
    }

    NODISCARD bool operator<=(const ArrayList* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] <= other;
    }

    NODISCARD bool operator>=(const ArrayList* other) const
    {
        if(_Size != 1)
            return false;

        return _Data[0] >= other;
    }

    Iterator<T> begin() const { return Iterator<T>(_Data); }
    Iterator<T> end() const { return Iterator<T>(_Data + _Size); }
private:
    void _Resize(unsigned int newSize)
    {
        T* newData = new T[newSize];

        for(unsigned int i = 0; i < _Size; i++)
        {
            newData[i] = _Data[i];
        }

        delete[] _Data;
        _Data = newData;
        _Capacity = newSize;

        delete[] newData;
        newData = nullptr;
    }

    void _Reset()
    {
        delete[] _Data;
        _Data = nullptr;
        _Size = 0;
        _Capacity = 0;
    }

    T* _Data;
    unsigned int _Size;
    unsigned int _Capacity;
};

} // Strand_Std
