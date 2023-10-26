// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Core.hpp>

namespace Strand_Std
{

class EXPORT_STRAND_STD String final
{
public:
    String();

    String(String& other);
    String(const char* other);
    String(unsigned int size);
    String(const char* target, unsigned int size);
    String(const unsigned char* target, unsigned int size);
    ~String();

    NODISCARD_INLINE unsigned int GetLength() const { return _Length; }

    NODISCARD_INLINE char* GetSource() const { return _Source; }

    NODISCARD_INLINE const char* GetSourceConst() const { return _Source; }

    NODISCARD int FindIndex(const String& targetString, unsigned int startIndex, unsigned int count = 0) const;
    NODISCARD int FindLastIndex(const String& targetString, unsigned int startIndex) const;
    NODISCARD unsigned int FindIndex(const char& targetChar) const;
    NODISCARD unsigned int FindIndex(const String& target) const;
    NODISCARD unsigned int GetCount(char targetChar) const;
    NODISCARD String GetSubset(unsigned int start, unsigned int length) const;

    void Clear();

    const char* operator*() const { return _Source; }

    String operator+=(const String& other);
    String operator+=(const char* other);
    String operator+=(char other);
    String operator-=(const char* other);
    String operator-=(const String& other);

    String operator=(const String& other);
    String operator=(const char* other);

    char operator[](unsigned int index) const { return _Source[index]; }

private:
    char* _Source;
    unsigned int _Length;
};

String operator+(const String& target0, const String& target1);
bool static operator==(const String& target0, const String& target1);
bool operator!=(const String& target0, const String& target1);

} // Strand_Std
