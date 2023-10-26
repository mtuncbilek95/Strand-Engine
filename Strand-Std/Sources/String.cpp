#include <String.hpp>

#include <Memory.hpp>

#define MAX_INT_DIGITS 20
#define MAX_FLOAT_DIGITS 20
#define MAX_LONGLONG_DIGITS 40

namespace Strand_Std
{
unsigned int GetCharPointerSize(const char* target)
{
    unsigned int size = 0;
    while(target[size] != '\0')
        size++;
    return size;
}

String::String()
{
    _Source = nullptr;
    _Length = 0;
}

String::String(String& other)
{
    _Length = other.GetLength();
    _Source = new char[_Length + 1];

    Memory::Copy(_Source, other.GetSource(), _Length);

    _Source[_Length] = '\0';
}

String::String(const char* other)
{
    _Length = GetCharPointerSize(other);
    _Source = new char[_Length + 1];

    Memory::Copy(_Source, other, _Length);

    _Source[_Length] = '\0';
}

String::String(const unsigned int size)
{
    _Length = size;
    _Source = new char[_Length + 1];

    for(unsigned int i = 0; i < _Length; i++)
        _Source[i] = '\0';

    _Source[_Length] = '\0';
}

String::String(const char* target, const unsigned int size)
{
    _Length = size;
    _Source = new char[_Length + 1];

    for(unsigned int i = 0; i < _Length; i++)
        _Source[i] = target[i];

    _Source[_Length] = '\0';
}

String::String(const unsigned char* target, unsigned int size)
{
    _Length = size;
    _Source = new char[_Length + 1];

    Memory::Copy((void*)target, _Source, size);

    _Source[_Length] = '\0';
}

String::~String()
{
    _Length = 0;
    delete[] _Source;
    _Source = nullptr;
}

int String::FindIndex(const String& targetString, const unsigned int startIndex, const unsigned int count) const
{
    if(startIndex >= _Length)
        return -1;

    unsigned int targetLength = targetString.GetLength();
    if(targetLength == 0)
        return -1;

    if(targetLength > _Length)
        return -1;

    unsigned int searchLength = _Length - targetLength;
    if(count > 0 && count < searchLength)
        searchLength = count;

    for(unsigned int i = startIndex; i < searchLength; i++)
    {
        if(_Source[i] == targetString[0])
        {
            bool found = true;
            for(unsigned int j = 1; j < targetLength; j++)
            {
                if(_Source[i + j] != targetString[j])
                {
                    found = false;
                    break;
                }
            }

            if(found)
                return i;
        }
    }

    return -1;
}

String String::GetSubset(unsigned int start, const unsigned int length) const
{
    unsigned int end = start + length;

    if (end >= _Length)
        return {};

    unsigned int gap = end - start;

    char* subsetSource = new char[gap + 1];

    int subsetIndex = 0;
    for(unsigned int i = start; i < end; i++)
    {
        subsetSource[subsetIndex] = _Source[i];
        subsetIndex++;
    }

    subsetSource[gap] = '\0';

    return String(subsetSource);
}

String String::operator=(const String& other)
{
    _Length = other.GetLength();
    _Source = new char[_Length + 1];
    Memory::Copy(other.GetSource(), _Source, _Length);
    _Source[_Length] = '\0';

    return String(_Source);
}

String String::operator=(const char* other)
{
    _Length = GetCharPointerSize(other);
    _Source = new char[_Length + 1];
    Memory::Copy(_Source, other, _Length);
    _Source[_Length] = '\0';

    return String(_Source);
}

int String::FindLastIndex(const String& targetString, const unsigned int startIndex) const
{
    if(startIndex >= _Length)
        return -1;

    unsigned int targetLength = targetString.GetLength();
    if(targetLength == 0)
        return -1;

    if(targetLength > _Length)
        return -1;

    unsigned int searchLength = _Length - targetLength;

    for(unsigned int i = searchLength; i > startIndex; i--)
    {
        if(_Source[i] == targetString[0])
        {
            bool found = true;
            for(unsigned int j = 1; j < targetLength; j++)
            {
                if(_Source[i + j] != targetString[j])
                {
                    found = false;
                    break;
                }
            }

            if(found)
                return i;
        }
    }

    return -1;
}

unsigned int String::FindIndex(const char& targetChar) const
{
    for(unsigned int i = 0; i < _Length; i++)
    {
        if(_Source[i] == targetChar)
            return i;
    }

    return -1;
}

unsigned int String::FindIndex(const String& target) const
{
    unsigned int targetLength = target.GetLength();
    if(targetLength == 0)
        return -1;

    if(targetLength > _Length)
        return -1;

    unsigned int searchLength = _Length - targetLength;

    for(unsigned int i = 0; i < searchLength; i++)
    {
        if(_Source[i] == target[0])
        {
            bool found = true;
            for(unsigned int j = 1; j < targetLength; j++)
            {
                if(_Source[i + j] != target[j])
                {
                    found = false;
                    break;
                }
            }

            if(found)
                return i;
        }
    }

    return -1;
}

unsigned int String::GetCount(const char targetChar) const
{
    unsigned int count = 0;
    for(unsigned int i = 0; i < _Length; i++)
    {
        if(_Source[i] == targetChar)
            count++;
    }

    return count;
}

String String::operator+=(const String& other)
{
    unsigned int otherLength = other.GetLength();
    unsigned int newLength = _Length + otherLength;

    char* newSource = new char[newLength + 1];

    Memory::Copy(newSource, _Source, _Length);
    Memory::Copy(newSource + _Length, other.GetSource(), otherLength);

    delete[] _Source;

    newSource[newLength] = '\0';

    _Source = newSource;
    _Length = newLength;

    return String(_Source);
}

String String::operator+=(const char* other)
{
    unsigned int otherLength = GetCharPointerSize(other);
    unsigned int newLength = _Length + otherLength;

    char* newSource = new char[newLength + 1];

    Memory::Copy(newSource, _Source, _Length);
    Memory::Copy(newSource + _Length, other, otherLength);

    delete[] _Source;

    newSource[newLength] = '\0';

    _Source = newSource;
    _Length = newLength;

    return String(_Source);
}

String String::operator+=(char other)
{
    unsigned int newLength = _Length + 1;

    char* newSource = new char[newLength + 1];

    Memory::Copy(newSource, _Source, _Length);
    newSource[_Length] = other;

    delete[] _Source;

    _Source = newSource;
    _Length = newLength;

    return String(_Source);
}

String String::operator-=(const char* other)
{
    unsigned int otherLength = GetCharPointerSize(other);
    unsigned int newLength = _Length - otherLength;

    char* newSource = new char[newLength + 1];

    unsigned int newSourceIndex = 0;
    for(unsigned int i = 0; i < _Length; i++)
    {
        bool found = false;
        for(unsigned int j = 0; j < otherLength; j++)
        {
            if(_Source[i] == other[j])
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            newSource[newSourceIndex] = _Source[i];
            newSourceIndex++;
        }
    }

    newSource[newLength] = '\0';

    delete[] _Source;

    _Source = newSource;
    _Length = newLength;

    return String(_Source);
}

String String::operator-=(const String& other)
{
    unsigned int otherLength = other.GetLength();
    unsigned int newLength = _Length - otherLength;

    char* newSource = new char[newLength + 1];

    unsigned int newSourceIndex = 0;
    for(unsigned int i = 0; i < _Length; i++)
    {
        bool found = false;
        for(unsigned int j = 0; j < otherLength; j++)
        {
            if(_Source[i] == other[j])
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            newSource[newSourceIndex] = _Source[i];
            newSourceIndex++;
        }
    }

    newSource[newLength] = '\0';

    delete[] _Source;

    _Source = newSource;
    _Length = newLength;

    return String(_Source);
}

void String::Clear()
{
    delete[] _Source;
    _Source = nullptr;
    _Length = 0;
}

bool static operator==(const String& target0, const String& target1)
{
    unsigned int target0Length = target0.GetLength();
    unsigned int target1Length = target1.GetLength();
    const char* target0Source = target0.GetSource();
    const char* target1Source = target1.GetSource();

    if (target0Length != target1Length)
        return false;

    for (unsigned int i = 0; i < target0Length; i++)
    {
        if (target0Source[i] != target1Source[i])
        {
            return false;
        }
    }

    return true;
}

String operator+(const String& target0, const String& target1)
{
    unsigned int target0Length = target0.GetLength();
    unsigned int target1Length = target1.GetLength();
    unsigned int newLength = target0Length + target1Length;

    char* newSource = new char[newLength + 1];

    Memory::Copy(newSource, target0.GetSource(), target0Length);
    Memory::Copy(newSource + target0Length, target1.GetSource(), target1Length);

    newSource[newLength] = '\0';

    return String(newSource);
}

bool operator!=(const String& target0, const String& target1)
{
    unsigned int target0Length = target0.GetLength();
    unsigned int target1Length = target1.GetLength();
    const char* target0Source = target0.GetSource();
    const char* target1Source = target1.GetSource();

    if (target0Length != target1Length)
        return true;

    for (unsigned int i = 0; i < target0Length; i++)
    {
        if (target0Source[i] != target1Source[i])
        {
            return true;
        }
    }

    return false;
}

} // Strand_Std