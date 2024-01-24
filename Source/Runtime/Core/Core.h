#pragma once

#if defined(_MSC_VER) && _MSC_VER >= 1910

typedef unsigned char uint8, byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

#define uint64_max 0xFFFFFFFFFFFFFFFF

#define NODISCARD [[nodiscard]]
#endif

namespace Strand
{
	enum class LogLevel
	{
		Info,
		Verbose,
		Warning,
		Error
	};

	void RUNTIME_API DevLog(LogLevel type, const char* pMessage, ...);
	void RUNTIME_API DevAssert(bool condition, const char* pTitle, const char* pFailed, ...);
}

#if defined(STRAND_DEBUG)

#define SE_INFO Strand::LogLevel::Info
#define SE_VERBOSE Strand::LogLevel::Verbose
#define SE_WARNING Strand::LogLevel::Warning
#define SE_ERROR Strand::LogLevel::Error

#define DEV_ASSERT(condition, title, message, ...) Strand::DevAssert(condition, title, message, __VA_ARGS__)
#define DEV_LOG(logType, message, ...) Strand::DevLog(logType, message, __VA_ARGS__)
#else
#define DEV_ASSERT(condition, title, message, ...) (condition)
#endif

#include <vector>
#include <memory>
#include <string>

template<typename T>
using ArrayList = std::vector<T>;
template<typename T, size_t N>
using Array = std::array<T, N>;
using String = std::string;
template<typename T>
using OwnedPtr = std::unique_ptr<T>;
template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T>
using EnableSharedFromThis = std::enable_shared_from_this<T>;

#include <glm/glm.hpp>
using namespace glm;

using Vector2f = fvec2;
using Vector3f = fvec3;
using Vector4f = fvec4;

using Vector2i = ivec2;
using Vector3i = ivec3;
using Vector4i = ivec4;

using Vector2u = uvec2;
using Vector3u = uvec3;
using Vector4u = uvec4;

using Matrix2f = mat2;
using Matrix3f = mat3;

using Quaternion = quat;

